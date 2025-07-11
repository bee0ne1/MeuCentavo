#include "pageHome.h"
#include "ui_pageHome.h"
#include "DataAccess/LancamentoDAO.h" // Essencial para buscar os dados
#include <QDate>
#include <QDebug>
#include <QHeaderView> // Para ajustar a tabela


pageHome::pageHome(const Usuario& usuario, QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageHome),
    m_usuarioAtual(usuario),
    m_db(db)
{
    ui->setupUi(this);

    // Configuração inicial da tabela (opcional, mas recomendado)
    ui->tabelaLancamentosRecentes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Faz a coluna "Descrição" esticar

    // Chama a função principal para carregar todos os dados quando a página é criada.
    atualizarDados();
}

pageHome::~pageHome()
{
    delete ui;
}

// Função principal que orquestra as atualizações
void pageHome::atualizarDados()
{
    carregarResumos();
    carregarTabelaRecentes();
}

// Função para preencher os cartões de resumo
void pageHome::carregarResumos()
{
    LancamentoDAO dao(m_db);
    QDate dataAtual = QDate::currentDate();

    double receitas = dao.obterSomaPorTipoNoMes(m_usuarioAtual.id, "Receita", dataAtual.month(), dataAtual.year());
    double despesas = dao.obterSomaPorTipoNoMes(m_usuarioAtual.id, "Despesa", dataAtual.month(), dataAtual.year());
    double saldo = receitas - despesas;

    // Formata os valores como moeda e exibe nos QLabels que você criou no .ui
    ui->labelValorReceitas->setText(QString("R$ %1").arg(receitas, 0, 'f', 2));
    ui->labelValorDespesas->setText(QString("R$ %1").arg(despesas, 0, 'f', 2));
    ui->labelSaldoMes->setText(QString("R$ %1").arg(saldo, 0, 'f', 2));

    // Bônus: Muda a cor do saldo para feedback visual
    if (saldo < 0) {
        ui->labelSaldoMes->setStyleSheet("color: #e74c3c;"); // Vermelho
    } else {
        ui->labelSaldoMes->setStyleSheet("color: #2ecc71;"); // Verde
    }
}

// Função para preencher a tabela de lançamentos recentes
void pageHome::carregarTabelaRecentes()
{
    // 1. Limpa a tabela para evitar dados duplicados ao atualizar
    ui->tabelaLancamentosRecentes->clearContents();
    ui->tabelaLancamentosRecentes->setRowCount(0);

    // 2. Busca os dados do banco
    LancamentoDAO dao(m_db);
    QVector<Lancamento> recentes = dao.obterLancamentosRecentes(m_usuarioAtual.id);

    // 3. Itera sobre os resultados e adiciona cada um como uma nova linha na tabela
    for (const auto& lancamento : recentes) {
        int linhaAtual = ui->tabelaLancamentosRecentes->rowCount();
        ui->tabelaLancamentosRecentes->insertRow(linhaAtual);

        // Cria os itens para cada célula
        QTableWidgetItem *itemData = new QTableWidgetItem(lancamento.data_lancamento.toString("dd/MM/yyyy"));
        QTableWidgetItem *itemDescricao = new QTableWidgetItem(lancamento.descricao);
        QTableWidgetItem *itemValor = new QTableWidgetItem(QString::number(lancamento.valor, 'f', 2));

        // Alinha o texto para melhor visualização
        itemData->setTextAlignment(Qt::AlignCenter);
        itemValor->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        // Colore o valor dependendo do tipo de lançamento
        if (lancamento.tipo == "Receita") {
            itemValor->setForeground(QColor("#2ecc71")); // Verde
        } else {
            itemValor->setForeground(QColor("#e74c3c")); // Vermelho
        }

        // Adiciona os itens na tabela, nas colunas corretas
        ui->tabelaLancamentosRecentes->setItem(linhaAtual, 0, itemData);
        ui->tabelaLancamentosRecentes->setItem(linhaAtual, 1, itemDescricao);
        ui->tabelaLancamentosRecentes->setItem(linhaAtual, 2, itemValor);
    }
}