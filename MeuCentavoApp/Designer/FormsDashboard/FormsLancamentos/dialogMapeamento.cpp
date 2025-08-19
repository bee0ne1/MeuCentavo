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
    m_categorias = categorias; // Guarda a lista completa
    m_categoriasReceita.clear();
    m_categoriasDespesa.clear();

    // Separa as categorias nas listas de Receita e Despesa
    for (const auto& cat : categorias) {
        if (cat.tipo == "Receita") {
            m_categoriasReceita.append(cat);
        } else {
            m_categoriasDespesa.append(cat);
        }
    }

    // Popula a tabela apenas DEPOIS de ter separado as categorias
    popularTabela();
}


void dialogMapeamento::popularTabela()
{
    ui->tableWidgetTransacoes->setRowCount(0);


    for (const auto& transacao : m_transacoes) {
        int linha = ui->tableWidgetTransacoes->rowCount();
        ui->tableWidgetTransacoes->insertRow(linha);

        ui->tableWidgetTransacoes->setItem(linha, 0, new QTableWidgetItem(transacao.dataStr));
        ui->tableWidgetTransacoes->setItem(linha, 1, new QTableWidgetItem(transacao.descricaoStr));

        // --- LÓGICA CORRIGIDA PARA SEPARAR ENTRADA E SAÍDA ---
        // Remove as aspas do tipo para uma comparação segura.
        QString tipoLimpo = transacao.tipoStr;
        tipoLimpo = tipoLimpo.remove('"').trimmed();

        if (tipoLimpo.compare("Receita", Qt::CaseInsensitive) == 0) {
            // Se for Receita, coloca o valor na coluna "Valor Entrada" (índice 2)
            ui->tableWidgetTransacoes->setItem(linha, 2, new QTableWidgetItem(transacao.valorStr));
            ui->tableWidgetTransacoes->setItem(linha, 3, new QTableWidgetItem("")); // Deixa a saída vazia
        } else {
            // Caso contrário (Despesa), coloca o valor na coluna "Valor Saída" (índice 3)
            ui->tableWidgetTransacoes->setItem(linha, 2, new QTableWidgetItem("")); // Deixa a entrada vazia
            ui->tableWidgetTransacoes->setItem(linha, 3, new QTableWidgetItem(transacao.valorStr));
        }
        // --- FIM DA CORREÇÃO ---

        QComboBox *comboCategoria = new QComboBox(this);
        comboCategoria->addItem("Ignorar esta transação", -1);

        // --- LÓGICA DE MAPEAMENTO INTELIGENTE ---

        Categoria categoriaCorrespondente;
        bool matchEncontrado = false;

        // Cria uma cópia local para modificação segura
        QString categoriaCsv = transacao.categoriaStr;
        categoriaCsv = categoriaCsv.remove('"').trimmed();

        // 1. Procura a categoria do CSV na lista COMPLETA de categorias do utilizador
        for(const auto& cat : m_categorias) {
            if (cat.nome.compare(categoriaCsv, Qt::CaseInsensitive) == 0) {
                categoriaCorrespondente = cat;
                matchEncontrado = true;
                break;
            }
        }

        // 2. Decide qual lista de categorias mostrar com base no TIPO da categoria encontrada
        if (matchEncontrado && categoriaCorrespondente.tipo == "Receita") {
            // Se encontrou e é do tipo Receita, mostra apenas categorias de receita
            for (const auto& cat : m_categoriasReceita) {
                comboCategoria->addItem(cat.nome, cat.id);
            }
        } else {
            // Em qualquer outro caso (é despesa, ou não encontrou), mostra as de despesa
            for (const auto& cat : m_categoriasDespesa) {
                comboCategoria->addItem(cat.nome, cat.id);
            }
        }

        // 3. Se encontrou uma correspondência, pré-seleciona-a no ComboBox
        if (matchEncontrado) {
            int index = comboCategoria->findData(categoriaCorrespondente.id);
            if (index != -1) {
                comboCategoria->setCurrentIndex(index);
            }
        }
        // --- FIM DA LÓGICA ---

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

