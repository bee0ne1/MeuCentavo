// Em dialogoMapeamento.cpp

#include "dialogMapeamento.h"
#include "ui_dialogMapeamento.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h"
#include <QComboBox>
#include <QCheckBox>
#include <QHeaderView>

dialogMapeamento::dialogMapeamento(QVector<TransacaoImportada>& transacoes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogMapeamento),
    m_transacoes(transacoes)
{
    ui->setupUi(this);
    setWindowTitle("Mapear e Confirmar Transações");
    setMinimumSize(800, 600); // Define um tamanho mínimo

    // Configura a tabela
    ui->tableWidgetTransacoes->setColumnCount(5);
    ui->tableWidgetTransacoes->setHorizontalHeaderLabels({"Data", "Descrição", "Valor Entrada", "Valor Saída", "Categoria"});
    ui->tableWidgetTransacoes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    m_dao = new LancamentoDAO(this);
    connect(m_dao, &LancamentoDAO::categoriasRecebidas, this, &dialogMapeamento::onCategoriasRecebidas);

    // Busca as categorias do usuário para preencher os ComboBoxes
    QString token = SessionManager::instance().getToken();
    m_dao->obterTodasCategorias(token);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

dialogMapeamento::~dialogMapeamento()
{
    delete ui;
}

void dialogMapeamento::onCategoriasRecebidas(const QVector<Categoria>& categorias)
{
    m_categorias = categorias;
    popularTabela(); // Popula a tabela assim que as categorias chegam
}

void dialogMapeamento::popularTabela()
{
    ui->tableWidgetTransacoes->setRowCount(0);

    for (const auto& transacao : m_transacoes) {
        int linha = ui->tableWidgetTransacoes->rowCount();
        ui->tableWidgetTransacoes->insertRow(linha);

        ui->tableWidgetTransacoes->setItem(linha, 0, new QTableWidgetItem(transacao.dataStr));
        ui->tableWidgetTransacoes->setItem(linha, 1, new QTableWidgetItem(transacao.descricaoStr));
        ui->tableWidgetTransacoes->setItem(linha, 2, new QTableWidgetItem(transacao.valorEntradaStr));
        ui->tableWidgetTransacoes->setItem(linha, 3, new QTableWidgetItem(transacao.valorSaidaStr));

        // Adiciona um ComboBox de Categorias na coluna 4
        QComboBox *comboCategoria = new QComboBox(this);
        comboCategoria->addItem("Selecione...", -1); // Opção padrão
        for (const auto& cat : m_categorias) {
            comboCategoria->addItem(cat.nome, cat.id);
        }
        ui->tableWidgetTransacoes->setCellWidget(linha, 4, comboCategoria);
    }
}

QVector<TransacaoImportada> dialogMapeamento::getTransacoesFinalizadas()
{
    // Percorre cada linha da tabela para ler as escolhas do usuário
    for (int i = 0; i < ui->tableWidgetTransacoes->rowCount(); ++i) {
        // Pega o ComboBox da célula na coluna 4
        QComboBox* combo = qobject_cast<QComboBox*>(ui->tableWidgetTransacoes->cellWidget(i, 4));
        if (combo) {
            // Pega o ID da categoria selecionada
            int idCategoria = combo->currentData().toInt();

            // Atualiza a transação correspondente no nosso vetor
            // Se o ID for -1 ("Selecione..."), a transação será ignorada
            m_transacoes[i].id_categoria = idCategoria;
        }
    }
    return m_transacoes;
}

