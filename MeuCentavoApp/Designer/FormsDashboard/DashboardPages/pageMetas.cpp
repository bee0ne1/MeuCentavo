#include "pageMetas.h"
#include "ui_pageMetas.h"
#include "DataAccess/MetaDAO.h"
#include "Gerenciamento/SessionManager.h"
#include "Designer/FormsDashboard/FormsMetas/dialogAddEditMeta.h"

// Includes para os widgets que usaremos
#include <QHeaderView>
#include <QProgressBar>
#include <QMessageBox>
#include <QDebug>

pageMetas::pageMetas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageMetas)
{
    ui->setupUi(this);

    // Instancia o DAO
    m_dao = new MetaDAO(this);

    // Configura a tabela
    ui->tableWidgetMetas->setColumnCount(5);
    ui->tableWidgetMetas->setHorizontalHeaderLabels({"Meta", "Progresso", "Valor Atual", "Valor Alvo", "Data Alvo"});
    ui->tableWidgetMetas->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch); // Coluna "Meta" estica
    ui->tableWidgetMetas->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidgetMetas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetMetas->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // Conecta os sinais do DAO aos nossos slots
    connect(m_dao, &MetaDAO::metasRecebidas, this, &pageMetas::onMetasRecebidas);
    connect(m_dao, &MetaDAO::onMetaError, this, &pageMetas::onErroDeRede);
    connect(m_dao, &MetaDAO::metaModificadaComSucesso, this, &pageMetas::onMetaModificada);
    // Conectaremos o sinal de 'metaModificada' quando implementarmos a adição/edição

    // Carrega os dados iniciais
    carregarMetas();
}

pageMetas::~pageMetas()
{
    delete ui;
}

void pageMetas::carregarMetas()
{
    QString token = SessionManager::instance().getToken();
    if (!token.isEmpty()) {
        m_dao->obterTodasMetas(token);
    }
}

void pageMetas::onMetasRecebidas(const QVector<Meta>& metas)
{
    m_metas = metas; // Salva a lista de metas recebida
    popularTabela(m_metas);
}

void pageMetas::popularTabela(const QVector<Meta>& metas)
{
    ui->tableWidgetMetas->setRowCount(0);

    for (const auto& meta : metas) {
        int linha = ui->tableWidgetMetas->rowCount();
        ui->tableWidgetMetas->insertRow(linha);

        // Coluna 0: Nome da Meta
        ui->tableWidgetMetas->setItem(linha, 0, new QTableWidgetItem(meta.nome));

        // Coluna 1: Barra de Progresso
        int percentual = (meta.valor_alvo > 0) ? (meta.valor_atual / meta.valor_alvo) * 100 : 0;
        QProgressBar *progressBar = new QProgressBar();
        progressBar->setRange(0, 100);
        progressBar->setValue(percentual);
        progressBar->setFormat(QString("%1%").arg(percentual));
        progressBar->setAlignment(Qt::AlignCenter);
        ui->tableWidgetMetas->setCellWidget(linha, 1, progressBar); // Adiciona o widget na célula

        // Lógica para símbolo dinâmico
        QString simbolo = "R$";
        if (meta.moeda_codigo == "USD") {
            simbolo = "$";
        } else if (meta.moeda_codigo == "EUR") {
            simbolo = "€";
        } // Adicione mais moedas aqui

        // Coluna 2: Valor Atual
        QString valorAtualFormatado = QString("%1 %2").arg(simbolo).arg(meta.valor_atual, 0, 'f', 2);
        QTableWidgetItem* itemValorAtual = new QTableWidgetItem(valorAtualFormatado);
        itemValorAtual->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tableWidgetMetas->setItem(linha, 2, itemValorAtual);

        // Coluna 3: Valor Alvo
        QString valorAlvoFormatado = QString("%1 %2").arg(simbolo).arg(meta.valor_alvo, 0, 'f', 2);
        QTableWidgetItem* itemValorAlvo = new QTableWidgetItem(valorAlvoFormatado);
        itemValorAlvo->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tableWidgetMetas->setItem(linha, 3, itemValorAlvo);

        // Coluna 4: Data Alvo
        ui->tableWidgetMetas->setItem(linha, 4, new QTableWidgetItem(meta.data_alvo.toString("dd/MM/yyyy")));

        // Alinha os valores à direita
        ui->tableWidgetMetas->item(linha, 2)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tableWidgetMetas->item(linha, 3)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}

void pageMetas::onMetaModificada()
{
    // Simplesmente recarrega a lista de metas da API
    carregarMetas();
}


void pageMetas::on_buttonAdicionar_clicked()
{
    dialogAddEditMeta dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Meta novaMeta = dialog.getMeta();
        QString token = SessionManager::instance().getToken();
        m_dao->adicionarMeta(novaMeta, token);
    }
}

void pageMetas::on_buttonEditar_clicked()
{
    int linhaAtual = ui->tableWidgetMetas->currentRow();
    if (linhaAtual < 0) {
        QMessageBox::warning(this, "Seleção Inválida", "Por favor, selecione uma meta na tabela para editar.");
        return;
    }

    Meta metaSelecionada = m_metas[linhaAtual];

    dialogAddEditMeta dialog(this);
    dialog.setMeta(metaSelecionada); // Preenche o diálogo com os dados atuais

    if (dialog.exec() == QDialog::Accepted) {
        Meta metaEditada = dialog.getMeta();
        // Preserva o valor atual, já que o diálogo de edição não o altera
        metaEditada.valor_atual = metaSelecionada.valor_atual;

        QString token = SessionManager::instance().getToken();
        m_dao->editarMeta(metaEditada, token);
    }
}

void pageMetas::on_buttonExcluir_clicked()
{
    int linhaAtual = ui->tableWidgetMetas->currentRow();
    if (linhaAtual < 0) {
        QMessageBox::warning(this, "Seleção Inválida", "Por favor, selecione uma meta na tabela para excluir.");
        return;
    }

    Meta metaSelecionada = m_metas[linhaAtual];

    auto resposta = QMessageBox::question(this, "Confirmar Exclusão",
        QString("Tem certeza que deseja excluir a meta '%1'?").arg(metaSelecionada.nome),
        QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        QString token = SessionManager::instance().getToken();
        m_dao->excluirMeta(metaSelecionada.id_meta, token);
    }
}


void pageMetas::onErroDeRede(const QString& motivo)
{
    QMessageBox::warning(this, "Erro de Rede", "Não foi possível carregar as metas: " + motivo);
}