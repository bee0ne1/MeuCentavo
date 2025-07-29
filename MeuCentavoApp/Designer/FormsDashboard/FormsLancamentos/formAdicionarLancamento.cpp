#include "formAdicionarLancamento.h"
#include "ui_formAdicionarLancamento.h"
#include "DataAccess/LancamentoDAO.h"
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

    // --- Configurações iniciais dos campos ---
    ui->comboBoxTipo->addItems({"Despesa", "Receita"});
    ui->dateEditData->setDate(QDate::currentDate());
    ui->spinBoxValor->setMinimum(0.01);
    ui->spinBoxValor->setMaximum(9999999.99);

    // --- Conectamos TODOS os sinais e slots aqui no construtor ---
    connect(ui->buttonSalvar, &QPushButton::clicked, this, &formAdicionarLancamento::salvarLancamento);
    connect(ui->buttonCancelar, &QPushButton::clicked, this, &QDialog::reject);

    // Conecta o DAO
    connect(m_dao, &LancamentoDAO::contasRecebidas, this, &formAdicionarLancamento::onContasRecebidas);
    connect(m_dao, &LancamentoDAO::categoriasRecebidas, this, &formAdicionarLancamento::onCategoriasRecebidas);
    connect(m_dao, &LancamentoDAO::lancamentoAdicionado, this, &formAdicionarLancamento::onLancamentoAdicionado);
    connect(m_dao, &LancamentoDAO::lancamentoModificadoComSucesso, this, &formAdicionarLancamento::onLancamentoAdicionado);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &formAdicionarLancamento::onErroDeRede);
    connect(m_dao, &LancamentoDAO::metasRecebidas, this, &formAdicionarLancamento::onMetasRecebidas);

    // Conecta o combobox de tipo ao nosso novo slot de filtro
    connect(ui->comboBoxTipo, &QComboBox::currentTextChanged, this, &formAdicionarLancamento::filtrarCategoriasPorTipo);

    // --- Inicia o carregamento dos dados ---
    QString token = SessionManager::instance().getToken();
    m_dao->obterTodasContas(token);
    m_dao->obterTodasCategorias(token);
    m_dao->obterTodasMetas(token);
}

formAdicionarLancamento::~formAdicionarLancamento()
{
    delete ui;
}

void formAdicionarLancamento::onContasRecebidas(const QVector<Conta>& contas)
{
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
    this->accept();
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

