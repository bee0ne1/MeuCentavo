#include "pageRelatorios.h"
#include "ui_pageRelatorios.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h"

// Includes do Qt Charts
#include <QtCharts>
#include <QPushButton>
#include <QGraphicsLayout>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QTimer>

pageRelatorios::pageRelatorios(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageRelatorios)
{
    ui->setupUi(this);

    // Instancia o DAO para comunicação com a API
    m_dao = new LancamentoDAO(this);

    // --- SETUP DO GRÁFICO DE PIZZA ---
    m_chart = new QChart();
    m_chart->setTitle("Gastos por Categoria (Mês Atual)");
    m_chart->setTheme(QChart::ChartThemeDark);
    m_chart->setAnimationOptions(QChart::AllAnimations);
    m_chart->setBackgroundVisible(false); // Fundo transparente

    // Configura a visualização do gráfico (QChartView)
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumHeight(400); // Garante altura mínima
    m_chartView->setBackgroundBrush(Qt::transparent);

    // Adiciona a visualização do gráfico ao layout definido no .ui
    ui->layoutGraficoPizza->addWidget(m_chartView);

    // --- SETUP DO NOVO GRÁFICO DE BARRAS ---
    m_chartBarras = new QChart();
    m_chartBarras->setTitle("Receitas vs. Despesas por Mês");
    m_chartBarras->setTheme(QChart::ChartThemeDark);
    m_chartBarras->setAnimationOptions(QChart::SeriesAnimations);
    m_chartBarras->setBackgroundVisible(false);

    m_chartViewBarras = new QChartView(m_chartBarras);
    m_chartViewBarras->setRenderHint(QPainter::Antialiasing);
    m_chartViewBarras->setMinimumHeight(300);
    ui->layoutGraficoBarras->addWidget(m_chartViewBarras); // Adiciona ao novo layout

    // 4. Conecta os sinais do DAO aos slots desta classe
    connect(m_dao, &LancamentoDAO::contasRecebidas, this, &pageRelatorios::onContasRecebidas);
    connect(m_dao, &LancamentoDAO::gastosPorCategoriaRecebidos, this, &pageRelatorios::onGastosRecebidos);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &pageRelatorios::onErroDeRede);
    connect(m_dao, &LancamentoDAO::lancamentosRecebidos, this, &pageRelatorios::onDetalhesRecebidos);
    connect(m_dao, &LancamentoDAO::comparativoMensalRecebido, this, &pageRelatorios::onComparativoRecebido);

    // Define as datas padrão nos QDateEdit
    ui->dateEditInicio->setDate(QDate::currentDate().addMonths(-1));
    ui->dateEditFim->setDate(QDate::currentDate());
    // Conecta o botão "Filtrar" para recarregar os dados
    connect(ui->buttonFiltrar, &QPushButton::clicked, this, &pageRelatorios::carregarDados);

    // Configura o cabeçalho da nova tabela
    ui->tableWidgetDetalhes->setColumnCount(4);
    ui->tableWidgetDetalhes->setHorizontalHeaderLabels({"Data", "Descrição", "Categoria", "Valor"});
    ui->tableWidgetDetalhes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // 5. Inicia o carregamento dos dados
    carregarDados();

    // No final do construtor, peça a lista de contas para preencher o combobox
    QString token = SessionManager::instance().getToken();
    m_dao->obterTodasContas(token);

}

pageRelatorios::~pageRelatorios()
{
    delete ui;
}

void pageRelatorios::carregarDados()
{
    qDebug() << "pageRelatorios: Requisitando dados de gastos por categoria...";
    QString token = SessionManager::instance().getToken();
    if (token.isEmpty()) {
        qDebug() << "pageRelatorios: Token inválido, carregamento cancelado.";
        return;
    }

    // Lê os valores dos filtros da UI
    QDate dataInicio = ui->dateEditInicio->date();
    QDate dataFim = ui->dateEditFim->date();
    // Pega o ID da conta do item selecionado no ComboBox
    int idConta = ui->comboBoxConta->currentData().toInt();

    // Chama o método do DAO com os filtros
    m_dao->obterGastosPorCategoria(token, dataInicio, dataFim, idConta);
    //busca os dados da tabela
    m_dao->obterTodos(token, dataInicio, dataFim, idConta);
    // Adiciona a chamada para o novo gráfico
    m_dao->obterComparativoMensal(token, dataInicio, dataFim, idConta);
}

void pageRelatorios::onGastosRecebidos(const QHash<QString, double>& dados)
{
    qDebug() << "pageRelatorios: Dados de gastos recebidos, atualizando gráfico.";
    m_chart->removeAllSeries(); // Limpa dados antigos

    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35); // Cria um efeito de "Donut Chart"
    series->setPieSize(0.7);   // Deixa uma margem em volta do gráfico

    // Adiciona os dados da API na série do gráfico
    for(auto it = dados.constBegin(); it != dados.constEnd(); ++it) {
        series->append(it.key(), it.value());
    }

    // Percorre cada "fatia" do gráfico para personalizá-la
    for(QPieSlice *slice : series->slices()) {
        slice->setLabelVisible(); // Garante que o rótulo seja visível
        slice->setLabelColor(Qt::white);
        slice->setLabel(QString("%1\n R$ %2 \n (%3%)")
            .arg(slice->label())
            .arg(slice->value())
            .arg(slice->percentage() * 100, 0, 'f', 1)); // Formato: Nome \n R$ Valor \n (XX.X%)

        // Efeito visual: ao passar o mouse, a fatia "explode" e a cor muda
        connect(slice, &QPieSlice::hovered, this, [=](bool hovered){
            if (hovered) {
                slice->setExploded(true);
                slice->setLabelFont(QFont("Arial", 11, QFont::Bold));
            } else {
                slice->setExploded(false);
                slice->setLabelFont(QFont("Arial", 9));
            }
        });
        connect(slice, &QPieSlice::clicked, this, [this, slice](){
            filtrarTabelaPorCategoria(slice->label().split("\n").first()); // Pega só o nome da categoria
        });
    }

    m_chart->addSeries(series);
}

void pageRelatorios::onContasRecebidas(const QVector<Conta>& contas)
{
    ui->comboBoxConta->clear();
    // Adiciona a opção "Todas" que terá o ID -1
    ui->comboBoxConta->addItem("Todas as Contas", -1);
    for (const auto& conta : contas) {
        ui->comboBoxConta->addItem(conta.nome, conta.id);
    }
}

void pageRelatorios::onErroDeRede(const QString& motivo)
{
    QMessageBox::warning(this, "Erro de Rede", "Não foi possível carregar os dados para os relatórios: " + motivo);
}

void pageRelatorios::onDetalhesRecebidos(const QVector<Lancamento>& lancamentos)
{
    m_lancamentosDoPeriodo = lancamentos; // Salva a lista completa
    popularTabelaDetalhes(m_lancamentosDoPeriodo); // Popula a tabela com todos os dados
}

void pageRelatorios::onComparativoRecebido(const QVector<ResumoMensal>& resumo)
{
    m_chartBarras->removeAllSeries();
    if(m_chartBarras->axisX()) m_chartBarras->removeAxis(m_chartBarras->axisX());
    if(m_chartBarras->axisY()) m_chartBarras->removeAxis(m_chartBarras->axisY());

    QBarSet *setReceitas = new QBarSet("Receitas");
    QBarSet *setDespesas = new QBarSet("Despesas");
    setReceitas->setColor(QColor("#2ecc71"));
    setDespesas->setColor(QColor("#e74c3c"));

    QStringList categories;

    for(const auto& r : resumo) {
        *setReceitas << r.receitas;
        *setDespesas << r.despesas;
        categories << r.mes;
    }

    QBarSeries *series = new QBarSeries();
    series->append(setReceitas);
    series->append(setDespesas);

    m_chartBarras->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    m_chartBarras->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    m_chartBarras->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    m_chartBarras->legend()->setVisible(true);
    m_chartBarras->legend()->setAlignment(Qt::AlignBottom);
}

void pageRelatorios::popularTabelaDetalhes(const QVector<Lancamento>& lancamentos)
{
    ui->tableWidgetDetalhes->setRowCount(0);
    for(const auto& lancamento : lancamentos) {
        int linha = ui->tableWidgetDetalhes->rowCount();
        ui->tableWidgetDetalhes->insertRow(linha);

        ui->tableWidgetDetalhes->setItem(linha, 0, new QTableWidgetItem(lancamento.data_lancamento.toString("dd/MM/yyyy")));
        ui->tableWidgetDetalhes->setItem(linha, 1, new QTableWidgetItem(lancamento.descricao));
        ui->tableWidgetDetalhes->setItem(linha, 2, new QTableWidgetItem(lancamento.nome_categoria));

        QTableWidgetItem *itemValor = new QTableWidgetItem(QString::number(lancamento.valor, 'f', 2));
        itemValor->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        if (lancamento.tipo == "Receita") {
            itemValor->setForeground(QColor("#2ecc71"));
        } else {
            itemValor->setForeground(QColor("#e74c3c"));
        }
        ui->tableWidgetDetalhes->setItem(linha, 3, itemValor);
    }
}

void pageRelatorios::filtrarTabelaPorCategoria(const QString& nomeCategoria)
{
    QVector<Lancamento> lancamentosFiltrados;
    for(const auto& lancamento : m_lancamentosDoPeriodo) {
        if(lancamento.nome_categoria == nomeCategoria) {
            lancamentosFiltrados.append(lancamento);
        }
    }
    popularTabelaDetalhes(lancamentosFiltrados); // Usa a mesma função de popular
}
