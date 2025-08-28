#include "formAdicionarLancamento.h"
#include "ui_formAdicionarLancamento.h"
#include "DataAccess/LancamentoDAO.h"
#include "DataAccess/ContaDAO.h"
#include "DataAccess/MetaDAO.h"
#include "Gerenciamento/SessionManager.h"
#include <QMessageBox>
#include <QDate>
#include <QDebug>

formAdicionarLancamento::formAdicionarLancamento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formAdicionarLancamento)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Adicionar Novo Lançamento");
    m_idLancamentoEdicao = -1; // -1 significa modo "Adicionar"

    // --- Instanciamos o DAO UMA ÚNICA VEZ ---
    m_dao = new LancamentoDAO(this);
    m_contaDao = new ContaDAO(this);
    m_metaDao = new MetaDAO(this);

    // --- Configurações iniciais dos campos ---
    ui->comboBoxTipo->addItems({"Despesa", "Receita"});
    ui->dateEditData->setDate(QDate::currentDate());
    ui->spinBoxValor->setMinimum(0.01);
    ui->spinBoxValor->setMaximum(9999999.99);

    // --- Conectamos TODOS os sinais e slots aqui no construtor ---
    connect(ui->buttonSalvar, &QPushButton::clicked, this, &formAdicionarLancamento::salvarLancamento);
    connect(ui->buttonCancelar, &QPushButton::clicked, this, &QDialog::reject);

    // Conecta o DAO
    connect(m_contaDao, &ContaDAO::contasRecebidas, this, &formAdicionarLancamento::onContasRecebidas);
    connect(m_contaDao, &ContaDAO::categoriasRecebidas, this, &formAdicionarLancamento::onCategoriasRecebidas);
    connect(m_dao, &LancamentoDAO::lancamentoAdicionado, this, &formAdicionarLancamento::onLancamentoAdicionado);
    connect(m_dao, &LancamentoDAO::lancamentoModificadoComSucesso, this, &formAdicionarLancamento::onLancamentoAdicionado);
    connect(m_contaDao, &ContaDAO::onContaError, this, &formAdicionarLancamento::onErroDeRede);
    connect(m_metaDao,&MetaDAO::onMetaError,this,&formAdicionarLancamento::onErroDeRede);
    connect(m_dao, &LancamentoDAO::onLancamentoError, this, &formAdicionarLancamento::onErroDeRede);

    connect(m_metaDao, &MetaDAO::metasRecebidas, this, &formAdicionarLancamento::onMetasRecebidas);

    // Conecta o combobox de tipo ao nosso novo slot de filtro
    connect(ui->comboBoxTipo, &QComboBox::currentTextChanged, this, &formAdicionarLancamento::filtrarCategoriasPorTipo);

    // --- Inicia o carregamento dos dados ---
    QString token = SessionManager::instance().getToken();
    m_contaDao->obterTodasContas(token);
    m_contaDao->obterTodasCategorias(token);
    m_metaDao->obterTodasMetas(token);
}

formAdicionarLancamento::~formAdicionarLancamento()
{
    delete ui;
}

void formAdicionarLancamento::onContasRecebidas(const QVector<Conta>& contas)
{
    m_contasDisponiveis = contas; // <-- ADICIONE: Salva a lista de contas
    for (const auto& conta : contas) {
        ui->comboBoxConta->addItem(conta.nome, conta.id);
    }
}

void formAdicionarLancamento::onCategoriasRecebidas(const QVector<Categoria>& categorias)
{
    m_todasCategorias = categorias; // Guarda a lista completa
    filtrarCategoriasPorTipo(); // Chama o filtro para exibir a lista inicial correta
}

void formAdicionarLancamento::filtrarCategoriasPorTipo()
{
    QString tipoSelecionado = ui->comboBoxTipo->currentText();
    ui->comboBoxCategoria->clear(); // Limpa as opções atuais

    for (const auto& categoria : m_todasCategorias) {
        // Adiciona a categoria ao combobox apenas se o tipo for o mesmo
        if (categoria.tipo == tipoSelecionado) {
            ui->comboBoxCategoria->addItem(categoria.nome, categoria.id);
        }
    }
    // --- LÓGICA DE BLOQUEIO DE METAS (ADICIONAR ESTE BLOCO) ---
    if (tipoSelecionado == "Despesa") {
        // Se for despesa, desabilita o campo de metas e seleciona "Nenhuma"
        ui->comboBoxMeta->setEnabled(false);
        ui->comboBoxMeta->setCurrentIndex(ui->comboBoxMeta->findData(-1)); // O -1 corresponde a "Nenhuma"
    } else {
        // Se for receita, habilita o campo de metas
        ui->comboBoxMeta->setEnabled(true);
    }
}

void formAdicionarLancamento::salvarLancamento()
{
    // 1. Validações (continuam iguais)
    if (ui->lineEditDescricao->text().isEmpty()) {
        QMessageBox::warning(this, "Campo Obrigatório", "A descrição não pode estar vazia.");
        return;
    }
    if (ui->comboBoxConta->currentIndex() == -1 || ui->comboBoxCategoria->currentIndex() == -1) {
        QMessageBox::warning(this, "Seleção Obrigatória", "Por favor, selecione uma conta e uma categoria.");
        return;
    }

    ui->buttonSalvar->setEnabled(false);
    ui->buttonSalvar->setText("Salvando...");

    // 2. Coleta os dados da interface (quase igual)
    Lancamento lancamento;
    lancamento.id = m_idLancamentoEdicao; // IMPORTANTE: Pega o ID que guardámos (-1 se for novo)
    lancamento.descricao = ui->lineEditDescricao->text();
    lancamento.valor = ui->spinBoxValor->value();
    lancamento.data_lancamento = ui->dateEditData->date();
    lancamento.tipo = ui->comboBoxTipo->currentText();
    lancamento.id_conta = ui->comboBoxConta->currentData().toInt();
    lancamento.id_categoria = ui->comboBoxCategoria->currentData().toInt();
    lancamento.id_meta = ui->comboBoxMeta->currentData().toInt();
    // --- LÓGICA CRÍTICA PARA MÚLTIPLAS MOEDAS ---
    lancamento.valor_original = ui->spinBoxValor->value();

    // Encontra a moeda da conta selecionada
    QString moedaDaConta = "BRL"; // Padrão
    for(const auto& conta : m_contasDisponiveis) {
        if (conta.id == lancamento.id_conta) {
            moedaDaConta = conta.moeda_codigo;
            break;
        }
    }
    lancamento.moeda_codigo_original = moedaDaConta;

    // TODO: No futuro, se a moeda for diferente da principal,
    // buscar a cotação e calcular o campo 'lancamento.valor' convertido.
    // Por agora, podemos deixar ambos iguais.
    lancamento.valor = lancamento.valor_original;
    lancamento.taxa_cambio_usada = 1;

    // --- LINHA DE DEBUG CRÍTICA ---
    qDebug() << "--- DADOS DO LANÇAMENTO A SER SALVO ---";
    qDebug() << "Descrição:" << lancamento.descricao;
    qDebug() << "Valor Original:" << lancamento.valor_original;
    qDebug() << "Moeda Original:" << lancamento.moeda_codigo_original;
    qDebug() << "ID da Conta:" << lancamento.id_conta;
    qDebug() << "------------------------------------";
    // --- FIM DO DEBUG ---

    QString token = SessionManager::instance().getToken();

    // 3. LÓGICA DE DECISÃO: Adicionar ou Editar?
    if (lancamento.id == -1) {
        // MODO ADICIONAR: O ID é -1, então chamamos o método de adicionar do DAO
        qDebug() << "Salvando NOVO lançamento...";
        m_dao->adicionarLancamento(lancamento, token);
    } else {
        // MODO EDITAR: O ID é válido, então chamamos o método de editar do DAO
        qDebug() << "Atualizando lançamento existente com ID:" << lancamento.id;
        m_dao->editarLancamento(lancamento, token);
    }
}

void formAdicionarLancamento::onLancamentoAdicionado()
{
    qDebug() << "Lançamento adicionado com sucesso, fechando diálogo.";
    emit lancamentoSalvo();
}

void formAdicionarLancamento::onErroDeRede(const QString& motivo)
{
    QMessageBox::critical(this, "Erro de Rede", motivo);
    ui->buttonSalvar->setEnabled(true);
    ui->buttonSalvar->setText("Salvar");
}

void formAdicionarLancamento::setLancamentoParaEdicao(const Lancamento& lancamento)
{
    setWindowTitle("Editar Lançamento");
    m_idLancamentoEdicao = lancamento.id;

    // Preenche os campos da UI com os dados do lançamento
    ui->lineEditDescricao->setText(lancamento.descricao);
    ui->spinBoxValor->setValue(lancamento.valor);
    ui->dateEditData->setDate(lancamento.data_lancamento);
    ui->comboBoxTipo->setCurrentText(lancamento.tipo);
    ui->comboBoxConta->setCurrentIndex(ui->comboBoxConta->findData(lancamento.id_conta));
    ui->comboBoxCategoria->setCurrentIndex(ui->comboBoxCategoria->findData(lancamento.id_categoria));
    ui->comboBoxMeta->setCurrentIndex(ui->comboBoxMeta->findData(lancamento.id_meta));
}


void formAdicionarLancamento::onMetasRecebidas(const QVector<Meta>& metas)
{
    ui->comboBoxMeta->clear();
    // A primeira opção permite não vincular o lançamento a nenhuma meta
    ui->comboBoxMeta->addItem("Nenhuma", -1); // -1 é um valor sentinela
    for (const auto& meta : metas) {
        ui->comboBoxMeta->addItem(meta.nome, meta.id_meta);
    }
}

