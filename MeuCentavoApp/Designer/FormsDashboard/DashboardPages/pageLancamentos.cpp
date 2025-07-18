#include "pageLancamentos.h"
#include "ui_pageLancamentos.h"
#include "Designer/FormsDashboard/formAdicionarLancamento.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h" // Inclui nosso "cofre" de sessão
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>

pageLancamentos::pageLancamentos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageLancamentos)
{
    ui->setupUi(this);
    m_dialogoAdicionar = nullptr;

    // Cria uma única instância do DAO para esta página
    m_dao = new LancamentoDAO(this);

    // Conecta os sinais de resultado do DAO aos nossos slots
    connect(m_dao, &LancamentoDAO::lancamentosRecebidos, this, &pageLancamentos::onLancamentosRecebidos);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &pageLancamentos::onErroDeRede);

    // Conecta o botão da UI ao slot que abre o diálogo
    connect(ui->buttonAdicionarLancamento, &QPushButton::clicked, this, &pageLancamentos::abrirDialogoAdicionar);

    // Configuração inicial da tabela
    ui->tabelaTodosLancamentos->setColumnCount(4);
    ui->tabelaTodosLancamentos->setHorizontalHeaderLabels({"Data", "Descrição", "Tipo", "Valor"});
    ui->tabelaTodosLancamentos->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // Inicia a busca por dados assim que a página é criada
    carregarTabela();
}

pageLancamentos::~pageLancamentos()
{
    delete ui;
}

void pageLancamentos::abrirDialogoAdicionar()
{
    if (!m_dialogoAdicionar) {
        // O diálogo agora também não precisa de parâmetros, pois ele pegará o ID do SessionManager
        m_dialogoAdicionar = new formAdicionarLancamento(this);
        m_dialogoAdicionar->setAttribute(Qt::WA_DeleteOnClose);

        // Conectamos o sinal de sucesso do diálogo ao nosso slot que recarrega a tabela
        connect(m_dialogoAdicionar, &formAdicionarLancamento::lancamentoSalvo, this, &pageLancamentos::carregarTabela);

        // Limpamos o ponteiro quando o diálogo for destruído
        connect(m_dialogoAdicionar, &QObject::destroyed, [this](){ m_dialogoAdicionar = nullptr; });
    }
    m_dialogoAdicionar->open();
}

void pageLancamentos::carregarTabela()
{
    qDebug() << "pageLancamentos: Requisitando lista de lançamentos da API...";
    // Pega o token do nosso "cofre" de sessão
    QString token = SessionManager::instance().getToken();

    // Inicia a requisição de rede e espera a resposta chegar no slot 'onLancamentosRecebidos'
    m_dao->obterTodos(token);
    emit dadosAtualizados();
}

void pageLancamentos::onLancamentosRecebidos(const QVector<Lancamento>& lancamentos)
{
    qDebug() << "pageLancamentos: Lista com" << lancamentos.count() << "lançamentos recebida. Atualizando tabela.";

    ui->tabelaTodosLancamentos->clearContents();
    ui->tabelaTodosLancamentos->setRowCount(0);

    for (const auto& lancamento : lancamentos) {
        qDebug() << "Adicionando à tabela -> Descricao:" << lancamento.descricao << "| Valor no objeto:" << lancamento.valor;
        int linha = ui->tabelaTodosLancamentos->rowCount();
        ui->tabelaTodosLancamentos->insertRow(linha);

        QTableWidgetItem *itemData = new QTableWidgetItem(lancamento.data_lancamento.toString("dd/MM/yyyy"));
        QTableWidgetItem *itemDesc = new QTableWidgetItem(lancamento.descricao);
        QTableWidgetItem *itemTipo = new QTableWidgetItem(lancamento.tipo);
        QTableWidgetItem *itemValor = new QTableWidgetItem(QString::number(lancamento.valor, 'f', 2));

        itemData->setTextAlignment(Qt::AlignCenter);
        itemValor->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        if (lancamento.tipo == "Receita") {
            itemValor->setForeground(QColor("#2ecc71")); // Verde
        } else {
            itemValor->setForeground(QColor("#e74c3c")); // Vermelho
        }

        ui->tabelaTodosLancamentos->setItem(linha, 0, itemData);
        ui->tabelaTodosLancamentos->setItem(linha, 1, itemDesc);
        ui->tabelaTodosLancamentos->setItem(linha, 2, itemTipo);
        ui->tabelaTodosLancamentos->setItem(linha, 3, itemValor);
    }
}

void pageLancamentos::onErroDeRede(const QString& motivo)
{
    QMessageBox::critical(this, "Erro de Rede", "Não foi possível buscar os lançamentos:\n" + motivo);
}