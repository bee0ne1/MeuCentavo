#include "pageInvestimentos.h"
#include "ui_pageInvestimentos.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h"
#include "Designer/FormsDashboard/FormsInvestimentos/dialogAddEditAtivo.h"
#include "Designer/FormsDashboard/FormsInvestimentos/dialogAddEditOperacao.h"
#include <QHeaderView>
#include <QMessageBox>

pageInvestimentos::pageInvestimentos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageInvestimentos)
{
    ui->setupUi(this);
    m_dao = new LancamentoDAO(this);

    ui->tableWidgetAtivos->setColumnCount(3);
    ui->tableWidgetAtivos->setHorizontalHeaderLabels({"Ticker", "Nome", "Tipo"});
    ui->tableWidgetAtivos->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->tableWidgetOperacoes->setColumnCount(5);
    ui->tableWidgetOperacoes->setHorizontalHeaderLabels({"Data", "Tipo", "Quantidade", "Preço Unitário", "Custos"});
    ui->tableWidgetOperacoes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(m_dao, &LancamentoDAO::ativosRecebidos, this, &pageInvestimentos::onAtivosRecebidos);
    connect(m_dao, &LancamentoDAO::ativoModificadoComSucesso, this, &pageInvestimentos::onAtivoModificado);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &pageInvestimentos::onErroDeRede);
    connect(m_dao, &LancamentoDAO::operacaoModificadaComSucesso, this, &pageInvestimentos::onAtivoSelecionado);
    connect(m_dao, &LancamentoDAO::ativoModificadoComSucesso, this, &pageInvestimentos::carregarAtivos);

    // Conecta o clique na tabela de ativos ao nosso novo slot
    connect(ui->tableWidgetAtivos, &QTableWidget::itemSelectionChanged, this, &pageInvestimentos::onAtivoSelecionado);

    // Conecta o sinal do DAO que trará as operações ao nosso slot
    connect(m_dao, &LancamentoDAO::operacoesRecebidas, this, &pageInvestimentos::onOperacoesRecebidas);

    carregarAtivos();
}

pageInvestimentos::~pageInvestimentos()
{
    delete ui;
}

void pageInvestimentos::carregarAtivos()
{
    QString token = SessionManager::instance().getToken();
    m_dao->obterTodosAtivos(token);
}

void pageInvestimentos::onAtivosRecebidos(const QVector<Ativo>& ativos)
{
    m_ativos = ativos;
    ui->tableWidgetAtivos->setRowCount(0);

    for (const auto& ativo : m_ativos) {
        int linha = ui->tableWidgetAtivos->rowCount();
        ui->tableWidgetAtivos->insertRow(linha);
        ui->tableWidgetAtivos->setItem(linha, 0, new QTableWidgetItem(ativo.ticker));
        ui->tableWidgetAtivos->setItem(linha, 1, new QTableWidgetItem(ativo.nome));
        ui->tableWidgetAtivos->setItem(linha, 2, new QTableWidgetItem(ativo.tipo_ativo));
    }
}

void pageInvestimentos::onAtivoModificado()
{
    carregarAtivos();
}

void pageInvestimentos::onErroDeRede(const QString& motivo)
{
    QMessageBox::warning(this, "Erro de Rede", motivo);
}

void pageInvestimentos::on_buttonAdicionarAtivo_clicked()
{
    dialogAddEditAtivo dialogo(this);
    if (dialogo.exec() == QDialog::Accepted) {
        Ativo novoAtivo = dialogo.getAtivo();
        QString token = SessionManager::instance().getToken();
        m_dao->adicionarAtivo(novoAtivo, token);
    }
}

// Adicione estas duas novas funções:
void pageInvestimentos::on_buttonEditarAtivo_clicked()
{
    int linhaAtual = ui->tableWidgetAtivos->currentRow();
    if (linhaAtual < 0) {
        QMessageBox::warning(this, "Seleção Inválida", "Por favor, selecione um ativo na tabela para editar.");
        return;
    }

    Ativo ativoSelecionado = m_ativos[linhaAtual];

    dialogAddEditAtivo dialogo(this);
    dialogo.setAtivo(ativoSelecionado);

    if (dialogo.exec() == QDialog::Accepted) {
        Ativo ativoEditado = dialogo.getAtivo();
        QString token = SessionManager::instance().getToken();
        m_dao->editarAtivo(ativoEditado, token);
    }
}

void pageInvestimentos::on_buttonExcluirAtivo_clicked()
{
    int linhaAtual = ui->tableWidgetAtivos->currentRow();
    if (linhaAtual < 0) {
        QMessageBox::warning(this, "Seleção Inválida", "Por favor, selecione um ativo na tabela para excluir.");
        return;
    }

    Ativo ativoSelecionado = m_ativos[linhaAtual];

    auto resposta = QMessageBox::question(this, "Confirmar Exclusão",
        QString("Tem certeza que deseja excluir o ativo '%1'?\nTodas as operações de compra e venda associadas a ele também serão removidas.")
        .arg(ativoSelecionado.ticker),
        QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        QString token = SessionManager::instance().getToken();
        m_dao->excluirAtivo(ativoSelecionado.id_ativo, token);
    }
}

void pageInvestimentos::onAtivoSelecionado()
{
    int linhaAtual = ui->tableWidgetAtivos->currentRow();
    ui->tableWidgetOperacoes->setRowCount(0); // Limpa a tabela de operações

    if (linhaAtual < 0) {
        return; // Nenhuma linha selecionada
    }

    // Pega o ativo correspondente à linha clicada
    Ativo ativoSelecionado = m_ativos[linhaAtual];

    // Pede ao DAO para buscar as operações deste ativo específico
    QString token = SessionManager::instance().getToken();
    m_dao->obterOperacoesDeAtivo(ativoSelecionado.id_ativo, token);
}

void pageInvestimentos::onOperacoesRecebidas(const QVector<OperacaoInvestimento>& operacoes)
{
    ui->tableWidgetOperacoes->setRowCount(0); // Garante que a tabela está limpa

    for (const auto& op : operacoes) {
        int linha = ui->tableWidgetOperacoes->rowCount();
        ui->tableWidgetOperacoes->insertRow(linha);

        ui->tableWidgetOperacoes->setItem(linha, 0, new QTableWidgetItem(op.data_operacao.toString("dd/MM/yyyy")));
        ui->tableWidgetOperacoes->setItem(linha, 1, new QTableWidgetItem(op.tipo_operacao));
        ui->tableWidgetOperacoes->setItem(linha, 2, new QTableWidgetItem(QString::number(op.quantidade, 'f', 4)));
        ui->tableWidgetOperacoes->setItem(linha, 3, new QTableWidgetItem(QString("R$ %1").arg(op.preco_unitario, 0, 'f', 2)));
        ui->tableWidgetOperacoes->setItem(linha, 4, new QTableWidgetItem(QString("R$ %1").arg(op.custos, 0, 'f', 2)));

        // Pinta a linha de verde para Compra e vermelho para Venda
        QColor cor = (op.tipo_operacao == "Compra") ? QColor("#d4edda") : QColor("#f8d7da");
        for(int i = 0; i < ui->tableWidgetOperacoes->columnCount(); ++i) {
            ui->tableWidgetOperacoes->item(linha, i)->setBackground(cor);
        }
    }
}

void pageInvestimentos::on_buttonRegistrarOperacao_clicked()
{
    int linhaAtual = ui->tableWidgetAtivos->currentRow();
    if (linhaAtual < 0) {
        QMessageBox::warning(this, "Seleção Inválida", "Por favor, selecione um ativo na tabela para registrar uma operação.");
        return;
    }

    Ativo ativoSelecionado = m_ativos[linhaAtual];

    dialogAddEditOperacao dialogo(ativoSelecionado, this);
    if (dialogo.exec() == QDialog::Accepted) {
        OperacaoInvestimento novaOperacao = dialogo.getOperacao();

        // Validação simples
        if (novaOperacao.quantidade <= 0 || novaOperacao.preco_unitario <= 0) {
            QMessageBox::warning(this, "Dados Inválidos", "A quantidade e o preço unitário devem ser maiores que zero.");
            return;
        }

        QString token = SessionManager::instance().getToken();
        m_dao->adicionarOperacao(novaOperacao, token);
    }
}