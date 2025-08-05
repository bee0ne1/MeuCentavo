#include "formGerenciarContas.h"
#include "ui_formGerenciarContas.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h"
#include "dialogAddEditConta.h" // O nosso novo diálogo de edição
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QHeaderView>

formGerenciarContas::formGerenciarContas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formGerenciarContas)
{
    ui->setupUi(this);
    setWindowTitle("Gerir Contas");

    m_dao = new LancamentoDAO(this);
    configurarTabela();

    connect(ui->buttonFechar, &QPushButton::clicked, this, &QDialog::accept);

    // Conexões do DAO
    connect(m_dao, &LancamentoDAO::contasRecebidas, this, &formGerenciarContas::onContasRecebidas);
    connect(m_dao, &LancamentoDAO::contaModificadaComSucesso, this, &formGerenciarContas::onContaModificada);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &formGerenciarContas::onErro);

    // Conexão da tabela
    connect(ui->tableWidgetContas, &QTableWidget::itemSelectionChanged, this, &formGerenciarContas::onSelectionChanged);

    onSelectionChanged(); // Estado inicial dos botões
    carregarContas();     // Carregar dados iniciais
}

formGerenciarContas::~formGerenciarContas()
{
    delete ui;
}

void formGerenciarContas::configurarTabela()
{
    QTableWidget* tabela = ui->tableWidgetContas;
    tabela->setColumnCount(4);
    tabela->setHorizontalHeaderLabels({"Nome", "Tipo", "Saldo Inicial", "Ações"});
    tabela->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tabela->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    tabela->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    tabela->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    // ... outras configurações ...
}

void formGerenciarContas::carregarContas()
{
    QString token = SessionManager::instance().getToken();
    m_dao->obterTodasContas(token);
}

void formGerenciarContas::onContasRecebidas(const QVector<Conta>& contas)
{
    ui->tableWidgetContas->blockSignals(true);
    ui->tableWidgetContas->setRowCount(0);

    for (const auto& conta : contas) {
        int linha = ui->tableWidgetContas->rowCount();
        ui->tableWidgetContas->insertRow(linha);

        // Coluna 0: Nome
        QTableWidgetItem* itemNome = new QTableWidgetItem(conta.nome);
        itemNome->setData(Qt::UserRole, QVariant::fromValue(conta));
        ui->tableWidgetContas->setItem(linha, 0, itemNome);

        // Coluna 1: Tipo
        ui->tableWidgetContas->setItem(linha, 1, new QTableWidgetItem(conta.tipo_conta));

        // Coluna 2: Saldo
        // --- LÓGICA PARA SÍMBOLO DINÂMICO DA MOEDA ---
        QString simbolo = "R$"; // Define "R$" como padrão
        if (conta.moeda_codigo == "USD") {
            simbolo = "$";
        } else if (conta.moeda_codigo == "EUR") {
            simbolo = "€";
        } // Adicione outros 'else if' para mais moedas aqui
        // Monta a string final com o símbolo correto
        QString saldoFormatado = QString("%1 %2").arg(simbolo).arg(conta.saldo_inicial, 0, 'f', 2);
        QTableWidgetItem* itemSaldo = new QTableWidgetItem(saldoFormatado);
        itemSaldo->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter); // Alinha o valor à direita
        ui->tableWidgetContas->setItem(linha, 2, itemSaldo);

        // Coluna 3: Ações
        QWidget* pWidget = new QWidget();
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        QPushButton* btnEdit = new QPushButton("Editar");
        QPushButton* btnDelete = new QPushButton("Excluir");
        btnEdit->setMinimumWidth(75);
        btnDelete->setMinimumWidth(75);
        pLayout->addWidget(btnEdit);
        pLayout->addWidget(btnDelete);
        pWidget->setLayout(pLayout);
        ui->tableWidgetContas->setCellWidget(linha, 3, pWidget);

        connect(btnEdit, &QPushButton::clicked, this, [this, conta](){ editarConta(conta); });
        connect(btnDelete, &QPushButton::clicked, this, [this, conta](){ excluirConta(conta); });
    }

    ui->tableWidgetContas->blockSignals(false);
    onSelectionChanged();
}

void formGerenciarContas::onContaModificada()
{
    carregarContas(); // Recarrega a lista após qualquer alteração
}

void formGerenciarContas::on_buttonAddConta_clicked()
{
    DialogAddEditConta dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Conta novaConta = dialog.getConta();
        QString token = SessionManager::instance().getToken();
        m_dao->adicionarConta(novaConta, token);
    }
}

void formGerenciarContas::on_buttonEditConta_clicked()
{
    QTableWidgetItem* item = ui->tableWidgetContas->currentItem();
    if (!item) return;
    Conta contaSelecionada = item->data(Qt::UserRole).value<Conta>();
    editarConta(contaSelecionada);
}

void formGerenciarContas::editarConta(const Conta& conta)
{
    DialogAddEditConta dialog(this);
    dialog.setConta(conta); // Pré-preenche o diálogo com os dados da conta
    if (dialog.exec() == QDialog::Accepted) {
        Conta contaEditada = dialog.getConta();
        QString token = SessionManager::instance().getToken();
        m_dao->editarConta(contaEditada, token);
    }
}

void formGerenciarContas::on_buttonExcluirConta_clicked()
{
    QTableWidgetItem* item = ui->tableWidgetContas->currentItem();
    if (!item) return;
    Conta contaSelecionada = item->data(Qt::UserRole).value<Conta>();
    excluirConta(contaSelecionada);
}

void formGerenciarContas::excluirConta(const Conta& conta)
{
    auto resposta = QMessageBox::question(this, "Confirmar Exclusão",
        QString("Tem certeza que deseja excluir a conta '%1'?").arg(conta.nome),
        QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        QString token = SessionManager::instance().getToken();
        m_dao->excluirConta(conta.id, token);
    }
}

void formGerenciarContas::onSelectionChanged()
{
    bool hasSelection = !ui->tableWidgetContas->selectedItems().isEmpty();
    ui->buttonEditConta->setEnabled(hasSelection);
    ui->buttonExcluirConta->setEnabled(hasSelection);
}

void formGerenciarContas::onErro(const QString& motivo)
{
    QMessageBox::warning(this, "Erro ao Modificar Conta", motivo);
}