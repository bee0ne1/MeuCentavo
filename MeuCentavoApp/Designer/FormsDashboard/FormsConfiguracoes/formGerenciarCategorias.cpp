#include "formGerenciarCategorias.h"
#include "ui_formGerenciarCategorias.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>

formGerenciarCategorias::formGerenciarCategorias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formGerenciarCategorias)
{
    ui->setupUi(this);
    setWindowTitle("Gerir Categorias");

    m_dao = new LancamentoDAO(this);
    ui->tabWidget->setTabText(0, "Despesas");
    ui->tabWidget->setTabText(1, "Receitas");
    configurarTabelas();

    connect(ui->buttonFechar, &QPushButton::clicked, this, &QDialog::accept);

    connect(m_dao, &LancamentoDAO::categoriasRecebidas, this, &formGerenciarCategorias::onCategoriasRecebidas);
    connect(m_dao, &LancamentoDAO::categoriaModificadaComSucesso, this, &formGerenciarCategorias::onCategoriaModificada);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, [](const QString& erro){
        QMessageBox::warning(nullptr, "Erro de Rede", erro);
    });

    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &formGerenciarCategorias::onSelectionChanged);
    connect(ui->tableWidget_2, &QTableWidget::itemSelectionChanged, this, &formGerenciarCategorias::onSelectionChanged);

    onSelectionChanged();
    carregarCategorias();
}

formGerenciarCategorias::~formGerenciarCategorias()
{
    delete ui;
}

void formGerenciarCategorias::configurarTabelas()
{
    // Usa a lista de tabelas para aplicar a mesma configuração a ambas
    QList<QTableWidget*> tabelas = {ui->tableWidget, ui->tableWidget_2};
    for (QTableWidget* tabela : tabelas) {
        tabela->setColumnCount(2);
        tabela->setHorizontalHeaderLabels({"Nome", "Ações"});

        // Pega o cabeçalho horizontal da tabela
        QHeaderView* header = tabela->horizontalHeader();

        // --- AQUI ESTÁ A CORREÇÃO ---
        // Coluna 0 (Nome): continua a esticar para preencher o espaço
        header->setSectionResizeMode(0, QHeaderView::Stretch);

        // Coluna 1 (Ações): agora tem um tamanho FIXO
        header->setSectionResizeMode(1, QHeaderView::Fixed);

        // Definimos a largura exata da coluna de Ações em pixels.
        // 170px deve ser suficiente para dois botões de 75px mais as margens.
        // Ajuste este valor se necessário.
        tabela->setColumnWidth(1, 170);
        // -----------------------------

        tabela->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabela->setSelectionMode(QAbstractItemView::SingleSelection);
        tabela->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tabela->verticalHeader()->setVisible(false);
    }
}
void formGerenciarCategorias::carregarCategorias()
{
    QString token = SessionManager::instance().getToken();
    if (!token.isEmpty()) {
        m_dao->obterTodasCategorias(token);
    }
}

void formGerenciarCategorias::onCategoriasRecebidas(const QVector<Categoria>& categorias)
{
    ui->tableWidget->blockSignals(true);
    ui->tableWidget_2->blockSignals(true);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget_2->setRowCount(0);

    for (const auto& categoria : categorias) {
        qDebug() << "Processando Categoria:" << categoria.nome << "| Tipo:" << categoria.tipo;

        QTableWidget* tabelaAlvo = (categoria.tipo == "Despesa") ? ui->tableWidget : ui->tableWidget_2;
        int linha = tabelaAlvo->rowCount();
        tabelaAlvo->insertRow(linha);

        QTableWidgetItem* itemNome = new QTableWidgetItem(categoria.nome);
        itemNome->setData(Qt::UserRole, QVariant::fromValue(categoria));
        tabelaAlvo->setItem(linha, 0, itemNome);

        QWidget* pWidget = new QWidget();
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        QPushButton* btnEdit = new QPushButton("Editar");
        QPushButton* btnDelete = new QPushButton("Excluir");
        btnEdit->setMinimumWidth(75);
        btnDelete->setMinimumWidth(75);
        pLayout->addWidget(btnEdit);
        pLayout->addWidget(btnDelete);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(5, 0, 5, 0); // Margens para não ficarem colados
        pWidget->setLayout(pLayout);
        tabelaAlvo->setCellWidget(linha, 1, pWidget);

        connect(btnEdit, &QPushButton::clicked, this, [this, categoria](){ editarCategoria(categoria); });
        connect(btnDelete, &QPushButton::clicked, this, [this, categoria](){ excluirCategoria(categoria); });
    }

    ui->tableWidget->blockSignals(false);
    ui->tableWidget_2->blockSignals(false);
    onSelectionChanged();
}

void formGerenciarCategorias::onCategoriaModificada()
{
    carregarCategorias();
}

QTableWidget* formGerenciarCategorias::tabelaAtual()
{
    return (ui->tabWidget->currentIndex() == 0) ? ui->tableWidget : ui->tableWidget_2;
}

void formGerenciarCategorias::onSelectionChanged()
{
    bool hasSelection = !tabelaAtual()->selectedItems().isEmpty();
    ui->buttonEditCategoria->setEnabled(hasSelection);
    ui->buttonExcluirCategoria->setEnabled(hasSelection);
}

void formGerenciarCategorias::on_buttonAddCategoria_clicked()
{
    bool ok;
    QString nome = QInputDialog::getText(this, "Adicionar Categoria", "Nome da nova categoria:", QLineEdit::Normal, "", &ok);
    if (ok && !nome.isEmpty())
    {
        Categoria novaCat;
        novaCat.nome = nome;
        novaCat.tipo = (ui->tabWidget->currentIndex() == 0) ? "Despesa" : "Receita";
        QString token = SessionManager::instance().getToken();
        m_dao->adicionarCategoria(novaCat, token);
    }
}

void formGerenciarCategorias::on_buttonEditCategoria_clicked()
{
    if (tabelaAtual()->currentColumn() != 0 && tabelaAtual()->currentColumn() != -1) return;
    QTableWidgetItem* item = tabelaAtual()->currentItem();
    if (!item) return;
    Categoria catSelecionada = item->data(Qt::UserRole).value<Categoria>();
    editarCategoria(catSelecionada);
}

void formGerenciarCategorias::on_buttonExcluirCategoria_clicked()
{
    if (tabelaAtual()->currentColumn() != 0 && tabelaAtual()->currentColumn() != -1) return;
    QTableWidgetItem* item = tabelaAtual()->currentItem();
    if (!item) return;
    Categoria catSelecionada = item->data(Qt::UserRole).value<Categoria>();
    excluirCategoria(catSelecionada);
}

void formGerenciarCategorias::editarCategoria(const Categoria& categoria)
{
    bool ok;
    QString novoNome = QInputDialog::getText(this, "Editar Categoria", "Novo nome:", QLineEdit::Normal, categoria.nome, &ok);
    if (ok && !novoNome.isEmpty() && novoNome != categoria.nome)
    {
        QString token = SessionManager::instance().getToken();
        m_dao->editarCategoria(categoria.id, novoNome, token);
    }
}

void formGerenciarCategorias::excluirCategoria(const Categoria& categoria)
{
    QMessageBox::StandardButton resposta = QMessageBox::question(this, "Confirmar Exclusão",
        QString("Tem certeza que deseja excluir a categoria '%1'?").arg(categoria.nome),
        QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        QString token = SessionManager::instance().getToken();
        m_dao->excluirCategoria(categoria.id, token);
    }
}