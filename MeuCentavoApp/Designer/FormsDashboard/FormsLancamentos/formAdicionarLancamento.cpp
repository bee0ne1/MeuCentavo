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
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &formAdicionarLancamento::onErroDeRede);

    // Conecta o combobox de tipo ao nosso novo slot de filtro
    connect(ui->comboBoxTipo, &QComboBox::currentTextChanged, this, &formAdicionarLancamento::filtrarCategoriasPorTipo);

    // --- Inicia o carregamento dos dados ---
    QString token = SessionManager::instance().getToken();
    m_dao->obterTodasContas(token);
    m_dao->obterTodasCategorias(token);
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
    if (ui->lineEditDescricao->text().isEmpty()) {
        QMessageBox::warning(this, "Campo Obrigatório", "A descrição não pode estar vazia.");
        return;
    }

    ui->buttonSalvar->setEnabled(false);
    ui->buttonSalvar->setText("Salvando...");

    Lancamento novoLancamento;
    novoLancamento.descricao = ui->lineEditDescricao->text();
    novoLancamento.valor = ui->spinBoxValor->value();
    novoLancamento.data_lancamento = ui->dateEditData->date();
    novoLancamento.tipo = ui->comboBoxTipo->currentText();
    novoLancamento.id_conta = ui->comboBoxConta->currentData().toInt();
    novoLancamento.id_categoria = ui->comboBoxCategoria->currentData().toInt();

    if (novoLancamento.id_conta == 0 || novoLancamento.id_categoria == 0) {
        QMessageBox::warning(this, "Seleção Obrigatória", "Por favor, selecione uma conta e uma categoria.");
        ui->buttonSalvar->setEnabled(true); // Reabilita o botão
        ui->buttonSalvar->setText("Salvar");
        return;
    }

    QString token = SessionManager::instance().getToken();

    // --- USA O DAO MEMBRO ---
    // Removemos a criação de um novo DAO aqui
    m_dao->adicionarLancamento(novoLancamento, token);
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