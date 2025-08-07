#include "pageDividas.h"
#include "ui_pageDividas.h"
#include "Gerenciamento/SessionManager.h"
#include "Designer/FormsDashboard/FormsDividas/dialogSimularPlano.h"
#include <QHeaderView>
#include <QProgressBar>
#include <QLocale>

pageDividas::pageDividas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageDividas)
{
    ui->setupUi(this);
    m_dao = new LancamentoDAO(this);

    // Configura a tabela
    ui->tableWidgetDividas->setColumnCount(6);
    ui->tableWidgetDividas->setHorizontalHeaderLabels({"Nome da Dívida", "Saldo Devedor", "Taxa de Juros", "Progresso", "Valor Original", "Data de Vencimento"});
    ui->tableWidgetDividas->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidgetDividas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetDividas->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Conecta o sinal do DAO ao slot que processa os dados
    connect(m_dao, &LancamentoDAO::contasRecebidas, this, &pageDividas::onDadosRecebidos);
}

pageDividas::~pageDividas()
{
    delete ui;
}

void pageDividas::carregarDados()
{
    // Pede ao DAO para buscar todas as contas. O filtro será feito no slot.
    QString token = SessionManager::instance().getToken();
    m_dao->obterTodasContas(token);
}

void pageDividas::onDadosRecebidos(const QVector<Conta>& contas)
{
    QVector<Conta> dividas;
    // 1. Filtra a lista para pegar apenas as contas que são dívidas
    for (const auto& conta : contas) {
        if (conta.tipo_conta == "Financiamento" || conta.tipo_conta == "Empréstimo" || conta.tipo_conta == "Cartão de Crédito") {
            dividas.append(conta);
        }
    }

    // 2. Calcula os totais para os cards
    double saldoDevedorTotal = 0;
    for (const auto& divida : dividas) {
        saldoDevedorTotal += divida.saldo_inicial; // 'saldo_inicial' aqui representa o saldo devedor atual
    }
    
    QLocale brLocale(QLocale::Portuguese, QLocale::Brazil);
    ui->labelSaldoDevedorTotal->setText(brLocale.toCurrencyString(saldoDevedorTotal));
    ui->labelNumeroDividas->setText(QString::number(dividas.size()));

    // 3. Popula a tabela
    ui->tableWidgetDividas->setRowCount(0);
    for (const auto& divida : dividas) {
        int linha = ui->tableWidgetDividas->rowCount();
        ui->tableWidgetDividas->insertRow(linha);

        // Coluna 0: Nome
        ui->tableWidgetDividas->setItem(linha, 0, new QTableWidgetItem(divida.nome));

        // Coluna 1: Saldo Devedor
        ui->tableWidgetDividas->setItem(linha, 1, new QTableWidgetItem(brLocale.toCurrencyString(divida.saldo_inicial)));

        // Coluna 2: Taxa de Juros
        ui->tableWidgetDividas->setItem(linha, 2, new QTableWidgetItem(QString::number(divida.taxa_juros, 'f', 2) + "% a.a."));

        // Coluna 3: Barra de Progresso
        double valorPago = divida.valor_total_divida - divida.saldo_inicial;
        int percentual = 0;
        if (divida.valor_total_divida > 0) {
            percentual = (valorPago / divida.valor_total_divida) * 100;
        }
        QProgressBar *progressBar = new QProgressBar();
        progressBar->setRange(0, 100);
        progressBar->setValue(percentual);
        progressBar->setFormat(QString("%1%").arg(percentual));
        progressBar->setAlignment(Qt::AlignCenter);
        ui->tableWidgetDividas->setCellWidget(linha, 3, progressBar);

        // Coluna 4: Valor Original
        ui->tableWidgetDividas->setItem(linha, 4, new QTableWidgetItem(brLocale.toCurrencyString(divida.valor_total_divida)));
        
        // Coluna 5: Data de Vencimento
        ui->tableWidgetDividas->setItem(linha, 5, new QTableWidgetItem(divida.data_vencimento.toString("dd/MM/yyyy")));
    }
}

void pageDividas::on_buttonPlanejarQuitacao_clicked()
{
    // Cria uma instância do seu novo diálogo de simulação
    // Passamos 'this' como pai para que ele se comporte como uma janela filha
    dialogSimularPlano* dialogo = new dialogSimularPlano(this);

    // Garante que a memória do diálogo seja liberada quando ele for fechado
    dialogo->setAttribute(Qt::WA_DeleteOnClose);

    // Abre o diálogo de forma não-modal (não bloqueia a janela principal)
    dialogo->open();
}