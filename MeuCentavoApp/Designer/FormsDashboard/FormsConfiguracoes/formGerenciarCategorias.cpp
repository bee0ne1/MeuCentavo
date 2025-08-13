#include "formGerenciarCategorias.h"
#include "ui_formGerenciarCategorias.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h"
#include "dialogAddEditCategoria.h"
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
    m_tipoPerfilAtivo = SessionManager::instance().getTipoPerfil();
    m_dao = new LancamentoDAO(this);
    ui->tabWidget->setTabText(0, "Despesas");
    ui->tabWidget->setTabText(1, "Receitas");
    configurarTabelas();

    connect(&SessionManager::instance(), &SessionManager::sessaoAtualizada, this, &formGerenciarCategorias::onSessaoAtualizada);

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
    QList<QTableWidget*> tabelas = {ui->tableWidget, ui->tableWidget_2};
    for (QTableWidget* tabela : tabelas) {

        if (m_tipoPerfilAtivo == "PJ") {
            // --- CONFIGURAÇÃO PARA PERFIL PJ (COM 3 COLUNAS) ---
            tabela->setColumnCount(3);
            tabela->setHorizontalHeaderLabels({"Nome", "Classificação Contábil", "Ações"});
            tabela->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch); // Nome
            tabela->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents); // Classificação
            tabela->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed); // Ações
            tabela->setColumnWidth(2, 170); // Largura fixa para os botões

        } else {
            // --- CONFIGURAÇÃO PARA PERFIL PF (COMO ESTAVA ANTES) ---
            tabela->setColumnCount(2);
            tabela->setHorizontalHeaderLabels({"Nome", "Ações"});
            tabela->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch); // Nome
            tabela->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed); // Ações
            tabela->setColumnWidth(1, 170);
        }

        // Configurações comuns a ambos os modos
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

    for (const auto& categoria : categorias)
    {
        QTableWidget* tabelaAlvo = (categoria.tipo == "Despesa") ? ui->tableWidget : ui->tableWidget_2;
        int linha = tabelaAlvo->rowCount();
        tabelaAlvo->insertRow(linha);

        // Coluna 0: Nome (comum a ambos os perfis)
        QTableWidgetItem* itemNome = new QTableWidgetItem(categoria.nome);
        itemNome->setData(Qt::UserRole, QVariant::fromValue(categoria));
        tabelaAlvo->setItem(linha, 0, itemNome);

        // Cria o widget de botões, que será usado em ambos os casos
        QWidget* pWidget = new QWidget();
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        QPushButton* btnEdit = new QPushButton("Editar");
        QPushButton* btnDelete = new QPushButton("Excluir");
        btnEdit->setMinimumWidth(75);
        btnDelete->setMinimumWidth(75);
        pLayout->addWidget(btnEdit);
        pLayout->addWidget(btnDelete);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(5, 0, 5, 0);
        pWidget->setLayout(pLayout);

        if (m_tipoPerfilAtivo == "PJ")
        {
            // --- LÓGICA PARA PERFIL PJ ---

            // Coluna 1: Classificação Contábil
            // --- CORREÇÃO AQUI: Adiciona o item à tabela ---
            QTableWidgetItem* itemClassificacao = new QTableWidgetItem(categoria.classificacao_contabil);
            tabelaAlvo->setItem(linha, 1, itemClassificacao);
            // --- FIM DA CORREÇÃO ---

            // Coluna 2: Ações
            tabelaAlvo->setCellWidget(linha, 2, pWidget);
        }
        else
        {
            // --- LÓGICA PARA PERFIL PF ---
            // Coluna 1: Ações
            tabelaAlvo->setCellWidget(linha, 1, pWidget);
        }

        // Conecta os botões (esta parte já estava correta)
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
    dialogAddEditCategoria dialogo(m_tipoPerfilAtivo, this);
    dialogo.setWindowTitle("Adicionar Nova Categoria");

    if (dialogo.exec() == QDialog::Accepted) {
        Categoria novaCat = dialogo.getDados();
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
    dialogAddEditCategoria dialogo(m_tipoPerfilAtivo, this);
    dialogo.setWindowTitle("Editar Categoria");
    dialogo.setDados(categoria);

    if (dialogo.exec() == QDialog::Accepted) {
        Categoria catEditada = dialogo.getDados();
        // O ID e o tipo não mudam, então os pegamos do objeto original
        catEditada.id = categoria.id;
        catEditada.tipo = categoria.tipo;

        QString token = SessionManager::instance().getToken();
        // O DAO precisa de uma função editarCategoria(Categoria, token)
        m_dao->editarCategoria(catEditada, token);
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

void formGerenciarCategorias::onSessaoAtualizada()
{
    qDebug() << "formGerenciarCategorias: Detectou atualização da sessão. Reconfigurando e recarregando...";

    // 1. Atualiza o estado interno da janela com o tipo do novo perfil.
    m_tipoPerfilAtivo = SessionManager::instance().getTipoPerfil();

    // 2. Reconfigura a aparência da tabela (adiciona/remove a coluna de classificação).
    configurarTabelas();

    // 3. Busca a nova lista de categorias para o perfil que agora está ativo.
    carregarCategorias();
}