#include "pageLancamentos.h"
#include "ui_pageLancamentos.h"
#include "Designer/FormsDashboard/formAdicionarLancamento.h"
#include "DataAccess/LancamentoDAO.h"
#include <QHeaderView>

pageLancamentos::pageLancamentos(const Usuario& usuario, QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageLancamentos),
    m_db(db),
    m_usuarioAtual(usuario)
{
    ui->setupUi(this);

    // Configuração inicial da tabela
    ui->tabelaTodosLancamentos->setColumnCount(4);
    ui->tabelaTodosLancamentos->setHorizontalHeaderLabels({"Data", "Descrição", "Tipo", "Valor"});
    ui->tabelaTodosLancamentos->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Descrição estica

    carregarTabela(); // Carrega os dados na primeira vez que a página é criada
}

pageLancamentos::~pageLancamentos()
{
    delete ui;
}

void pageLancamentos::on_buttonAdicionarLancamento_clicked()
{
    // Cria o diálogo, passando o ID do usuário e a conexão com o banco
    formAdicionarLancamento dialogo(m_usuarioAtual.id, m_db, this);

    // --- A CONEXÃO PARA O REFRESH AUTOMÁTICO ---
    // Conecta o sinal do diálogo ao slot que recarrega a tabela desta página.
    connect(&dialogo, &formAdicionarLancamento::lancamentoSalvo, this, &pageLancamentos::carregarTabela);

    // Executa o diálogo de forma modal
    dialogo.exec();
}

void pageLancamentos::carregarTabela()
{
    // Lógica para preencher a tabela (muito similar à da pageHome)
    ui->tabelaTodosLancamentos->clearContents();
    ui->tabelaTodosLancamentos->setRowCount(0);

    LancamentoDAO dao(m_db);
    // Você precisará criar este método no DAO, que busca TODOS os lançamentos, não apenas os recentes
    QVector<Lancamento> lancamentos = dao.obterTodosLancamentosPorUsuario(m_usuarioAtual.id);

    for (const auto& lancamento : lancamentos) {
        // ... Lógica para criar os QTableWidgetItems e popular a tabela ...
    }
}


