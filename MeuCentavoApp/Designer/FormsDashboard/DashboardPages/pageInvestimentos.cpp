#include "pageInvestimentos.h"
#include "ui_pageInvestimentos.h"
#include "DataAccess/InvestimentoDAO.h"
#include "Gerenciamento/SessionManager.h"
#include "Designer/FormsDashboard/FormsInvestimentos/dialogAddEditAtivo.h"
#include "Designer/FormsDashboard/FormsInvestimentos/dialogAddEditOperacao.h"
#include "Designer/FormsDashboard/FormsInvestimentos/dialogAddDividendo.h"
#include "Modelo/Dividendo.h"
#include <QHeaderView>
#include <QMessageBox>

pageInvestimentos::pageInvestimentos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageInvestimentos)
{
    ui->setupUi(this);
    m_dao = new InvestimentoDAO(this);

    ui->tableWidgetAtivos->setColumnCount(5);
    ui->tableWidgetAtivos->setHorizontalHeaderLabels({"Ticker", "Nome", "Quantidade Total", "Preço Médio", "Custo Total"});
    ui->tableWidgetAtivos->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->tableWidgetOperacoes->setColumnCount(5);
    ui->tableWidgetOperacoes->setHorizontalHeaderLabels({"Data", "Tipo", "Quantidade", "Preço Unitário", "Custos"});
    ui->tableWidgetOperacoes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetDividendos->setColumnCount(2);
    ui->tableWidgetDividendos->setHorizontalHeaderLabels({"Data Pagamento", "Valor Recebido"});
    ui->tableWidgetDividendos->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidgetDividendos->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);



    connect(m_dao, &InvestimentoDAO::ativosRecebidos, this, &pageInvestimentos::onAtivosRecebidos);
    connect(m_dao, &InvestimentoDAO::ativoModificadoComSucesso, this, &pageInvestimentos::onAtivoModificado);
    connect(m_dao, &InvestimentoDAO::onInvestimentoError, this, &pageInvestimentos::onErroDeRede);
    connect(m_dao, &InvestimentoDAO::operacaoModificadaComSucesso, this, &pageInvestimentos::onAtivoSelecionado);
    connect(m_dao, &InvestimentoDAO::ativoModificadoComSucesso, this, &pageInvestimentos::carregarAtivos);
    connect(m_dao, &InvestimentoDAO::performancePortfolioRecebida, this, &pageInvestimentos::onPerformanceRecebida);
    connect(m_dao, &InvestimentoDAO::dividendosRecebidos, this, &pageInvestimentos::onDividendosRecebidos);
    connect(m_dao, &InvestimentoDAO::dividendoAdicionadoComSucesso, this, &pageInvestimentos::onAtivoSelecionado); // Recarrega a lista após adicionar

    // Conecta o clique na tabela de ativos ao nosso novo slot
    connect(ui->tableWidgetAtivos, &QTableWidget::itemSelectionChanged, this, &pageInvestimentos::onAtivoSelecionado);

    // Conecta o sinal do DAO que trará as operações ao nosso slot
    connect(m_dao, &InvestimentoDAO::operacoesRecebidas, this, &pageInvestimentos::onOperacoesRecebidas);

    carregarAtivos();
}

pageInvestimentos::~pageInvestimentos()
{
    delete ui;
}

void pageInvestimentos::carregarAtivos()
{
    QString token = SessionManager::instance().getToken();
    m_dao->obterPortfolioConsolidado(token);
    m_dao->obterPerformancePortfolio(token);
}

void pageInvestimentos::onAtivosRecebidos(const QVector<Ativo>& ativos)
{
    m_ativos = ativos;
    ui->tableWidgetAtivos->setRowCount(0);

    for (const auto& ativo : m_ativos) {
        int linha = ui->tableWidgetAtivos->rowCount();
        ui->tableWidgetAtivos->insertRow(linha);

        // Calcula o preço médio (evitando divisão por zero)
        double precoMedio = (ativo.quantidade_total > 0) ? (ativo.custo_total / ativo.quantidade_total) : 0.0;

        ui->tableWidgetAtivos->setItem(linha, 0, new QTableWidgetItem(ativo.ticker));
        ui->tableWidgetAtivos->setItem(linha, 1, new QTableWidgetItem(ativo.nome));
        ui->tableWidgetAtivos->setItem(linha, 2, new QTableWidgetItem(QString::number(ativo.quantidade_total, 'f', 4)));
        ui->tableWidgetAtivos->setItem(linha, 3, new QTableWidgetItem(QString("R$ %1").arg(precoMedio, 0, 'f', 2)));
        ui->tableWidgetAtivos->setItem(linha, 4, new QTableWidgetItem(QString("R$ %1").arg(ativo.custo_total, 0, 'f', 2)));
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

    // Pede ao DAO para buscar as operações e os dividendos deste ativo específico
    QString token = SessionManager::instance().getToken();
    m_dao->obterOperacoesDeAtivo(ativoSelecionado.id_ativo, token);
    m_dao->obterDividendosDeAtivo(ativoSelecionado.id_ativo, token);
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

        // O fundo da célula agora será controlado pela folha de estilos.
        // Nós mudamos apenas a COR DO TEXTO para indicar o tipo.
        QColor corTexto = (op.tipo_operacao == "Compra") ? QColor("#2ecc71") : QColor("#e74c3c");

        // Aplica a cor do texto a todos os itens da linha
        for(int i = 0; i < ui->tableWidgetOperacoes->columnCount(); ++i) {
            if(ui->tableWidgetOperacoes->item(linha, i)) { // Garante que o item existe
                ui->tableWidgetOperacoes->item(linha, i)->setForeground(corTexto);
            }
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

// Slot para o clique do botão "Registrar Dividendo"
void pageInvestimentos::on_buttonRegistrarDividendo_clicked()
{
    int linhaAtual = ui->tableWidgetAtivos->currentRow();
    if (linhaAtual < 0) {
        QMessageBox::warning(this, "Seleção Inválida", "Por favor, selecione um ativo na tabela para registrar um dividendo.");
        return;
    }

    Ativo ativoSelecionado = m_ativos[linhaAtual];

    // Cria e abre o novo diálogo
    dialogAddDividendo dialogo(ativoSelecionado, this); // Supondo que o construtor peça o ativo
    if (dialogo.exec() == QDialog::Accepted) {
        Dividendo novoDividendo = dialogo.getDividendo(); // Supondo que o diálogo tenha esta função
        QString token = SessionManager::instance().getToken();
        m_dao->adicionarDividendo(novoDividendo, token);
    }
}


void pageInvestimentos::onPerformanceRecebida(double custoTotal, double valorMercado, double rentabilidadeValor, double rentabilidadePercentual)
{
    QLocale locale("pt_BR"); // Para formatação em Reais

    ui->labelCustoTotal->setText(locale.toCurrencyString(custoTotal));
    ui->labelValorMercado->setText(locale.toCurrencyString(valorMercado));

    QString rentabilidadeTexto = QString("%1 (%2%)")
                                     .arg(locale.toCurrencyString(rentabilidadeValor))
                                     .arg(QString::number(rentabilidadePercentual, 'f', 2));
    ui->labelRentabilidade->setText(rentabilidadeTexto);

    // Lógica de cores para lucro/prejuízo
    if (rentabilidadeValor > 0) {
        ui->labelRentabilidade->setStyleSheet("color: #2ecc71; font-weight: bold;"); // Verde
    } else if (rentabilidadeValor < 0) {
        ui->labelRentabilidade->setStyleSheet("color: #e74c3c; font-weight: bold;"); // Vermelho
    } else {
        ui->labelRentabilidade->setStyleSheet("color: white; font-weight: bold;"); // Cor padrão
    }
}

// Slot para popular a tabela quando os dividendos chegarem da API
void pageInvestimentos::onDividendosRecebidos(const QVector<Dividendo>& dividendos)
{
    ui->tableWidgetDividendos->setRowCount(0);
    QLocale brLocale(QLocale::Portuguese, QLocale::Brazil);

    for (const auto& dividendo : dividendos) {
        int linha = ui->tableWidgetDividendos->rowCount();
        ui->tableWidgetDividendos->insertRow(linha);

        // Coluna 0: Data
        QTableWidgetItem *itemData = new QTableWidgetItem(dividendo.data_pagamento.toString("dd/MM/yyyy"));
        ui->tableWidgetDividendos->setItem(linha, 0, itemData);

        // Coluna 1: Valor
        // Assumimos que o dividendo está sempre em BRL, mas podemos adaptar se necessário
        QString valorFormatado = brLocale.toCurrencyString(dividendo.valor_total);
        QTableWidgetItem *itemValor = new QTableWidgetItem(valorFormatado);
        itemValor->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        itemValor->setForeground(QColor("#2ecc71")); // Verde para indicar entrada de dinheiro
        ui->tableWidgetDividendos->setItem(linha, 1, itemValor);
    }
}