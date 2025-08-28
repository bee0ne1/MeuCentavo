// Em dialogoMapeamento.cpp

#include "dialogMapeamento.h"
#include "ui_dialogMapeamento.h"
#include "DataAccess/LancamentoDAO.h"
#include "DataAccess/ContaDAO.h"
#include "Gerenciamento/SessionManager.h"
#include <QComboBox>
#include <QCheckBox>
#include <QHeaderView>

dialogMapeamento::dialogMapeamento(QVector<TransacaoImportada>& transacoes, const QMap<QString, int>& sugestoes, QWidget *parent) :    QDialog(parent),
    ui(new Ui::dialogMapeamento),
    m_transacoes(transacoes),
    m_sugestoes(sugestoes) // <-- Armazena as sugestões
{
    ui->setupUi(this);
    setWindowTitle("Mapear e Confirmar Transações");
    setMinimumSize(800, 600); // Define um tamanho mínimo

    // Configura a tabela
    ui->tableWidgetTransacoes->setColumnCount(5);
    ui->tableWidgetTransacoes->setHorizontalHeaderLabels({"Data", "Descrição", "Valor Entrada", "Valor Saída", "Categoria"});
    ui->tableWidgetTransacoes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    m_dao = new ContaDAO(this);
    connect(m_dao, &ContaDAO::categoriasRecebidas, this, &dialogMapeamento::onCategoriasRecebidas);

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

        // A sua lógica para separar Entradas e Saídas (que já estava correta)
        QString tipoLimpoParaValor = transacao.tipoStr;
        tipoLimpoParaValor = tipoLimpoParaValor.remove('"').trimmed();

        if (tipoLimpoParaValor.compare("Receita", Qt::CaseInsensitive) == 0) {
            ui->tableWidgetTransacoes->setItem(linha, 2, new QTableWidgetItem(transacao.valorStr));
            ui->tableWidgetTransacoes->setItem(linha, 3, new QTableWidgetItem(""));
        } else {
            ui->tableWidgetTransacoes->setItem(linha, 2, new QTableWidgetItem(""));
            ui->tableWidgetTransacoes->setItem(linha, 3, new QTableWidgetItem(transacao.valorStr));
        }

        QComboBox *comboCategoria = new QComboBox(this);
        comboCategoria->addItem("Ignorar esta transação", -1);



        // --- LÓGICA DE MAPEAMENTO INTELIGENTE (VERSÃO CORRIGIDA) ---

        // 1. Determine qual lista de categorias é válida para esta transação específica
        QString tipoLimpo = transacao.tipoStr;
        tipoLimpo = tipoLimpo.remove('"').trimmed();
        const auto& listaDeCategoriasValidas = (tipoLimpo.compare("Receita", Qt::CaseInsensitive) == 0)
                                               ? m_categoriasReceita
                                               : m_categoriasDespesa;

        // 2. Popule o ComboBox APENAS com as categorias válidas
        for (const auto& cat : listaDeCategoriasValidas) {
            comboCategoria->addItem(cat.nome, cat.id);
        }

        // 3. Agora, com o ComboBox já preenchido, tente encontrar uma sugestão para pré-selecionar
        int idParaSelecionar = -1;

        // Primeiro, tente a sugestão da API
        QString descricaoLimpa = transacao.descricaoStr;
        descricaoLimpa = descricaoLimpa.remove('"').trimmed();


        if (m_sugestoes.contains(descricaoLimpa)) {
            idParaSelecionar = m_sugestoes.value(descricaoLimpa);
        }

        // Se a API não sugeriu nada, tente o fallback do nome da categoria no arquivo CSV
        if (idParaSelecionar <= 0) {
            QString categoriaCsv = transacao.categoriaStr;
            categoriaCsv = categoriaCsv.remove('"').trimmed();
            // Procure o nome da categoria SOMENTE na lista de categorias válidas
            for(const auto& cat : listaDeCategoriasValidas) {
                if (cat.nome.compare(categoriaCsv, Qt::CaseInsensitive) == 0) {
                    idParaSelecionar = cat.id;
                    break;
                }
            }
        }

        // 4. Finalmente, tente definir o índice no ComboBox
        if (idParaSelecionar > 0) {
            // O findData agora buscará o ID somente entre as opções válidas que foram adicionadas
            int index = comboCategoria->findData(idParaSelecionar);
            if (index != -1) { // Se o ID foi encontrado na lista
                comboCategoria->setCurrentIndex(index);
            }
        }
        // --- FIM DA CORREÇÃO ---

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

