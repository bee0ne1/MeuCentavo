#include "pageHome.h"
#include "ui_pageHome.h"
#include "DataAccess/LancamentoDAO.h"
#include "DataAccess/RelatorioDAO.h"
#include "Gerenciamento/SessionManager.h" // Nosso "cofre" de sessão
#include <QHeaderView>
#include <QMessageBox>
#include <QtCharts>



pageHome::pageHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageHome)
{
    ui->setupUi(this);

    // Cria uma única instância do DAO para esta página
    m_dao = new LancamentoDAO(this);
    m_relatorio = new RelatorioDAO(this);
    m_chart = new QChart();
    m_chart->setTitle("Resumo Mensal");
    m_chart->setTheme(QChart::ChartThemeDark);
    m_chart->setAnimationOptions(QChart::SeriesAnimations);

    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumHeight(250);

    // --- SETUP DO NOVO GRÁFICO DE PATRIMÔNIO ---
    m_chartPatrimonio = new QChart();
    m_chartPatrimonio->setTitle("Evolução do Patrimônio");
    m_chartPatrimonio->setTheme(QChart::ChartThemeDark);
    m_chartPatrimonio->setAnimationOptions(QChart::SeriesAnimations);

    m_chartViewPatrimonio = new QChartView(m_chartPatrimonio);
    m_chartViewPatrimonio->setRenderHint(QPainter::Antialiasing);
    ui->layoutGraficoPatrimonio->addWidget(m_chartViewPatrimonio); // Adiciona ao novo layout


    // Conecta os sinais de resultado do DAO aos nossos slots
    connect(m_relatorio, &RelatorioDAO::resumosRecebidos, this, &pageHome::onResumosRecebidos);
    connect(m_dao, &LancamentoDAO::lancamentosRecebidos, this, &pageHome::onLancamentosRecentesRecebidos);
    connect(m_dao, &LancamentoDAO::onLancamentoError, this, &pageHome::onErroDeRede);
    connect(m_relatorio, &RelatorioDAO::historicoPatrimonioRecebido, this, &pageHome::onHistoricoPatrimonioRecebido);
    connect(m_relatorio, &RelatorioDAO::onRelatorioError, this, &pageHome::onErroDeRede);


    // Configuração inicial da tabela
    ui->tabelaLancamentosRecentes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    // Adiciona a view do gráfico ao layout que você criou no Qt Designer
    ui->layoutGraficoResumo->addWidget(m_chartView);
    //ui->layoutGraficoResumo->parentWidget()->setStyleSheet("border: 1px solid red;");

    // Inicia a busca por dados assim que a página é criada
    atualizarDados();
}

pageHome::~pageHome()
{
    delete ui;
}

void pageHome::atualizarDados()
{
    // Pega o token e o ID do usuário do nosso "cofre" de sessão
    QString token = SessionManager::instance().getToken();
    int usuarioId = SessionManager::instance().getUsuarioId();

    if (!SessionManager::instance().estaLogado()) {
        qDebug() << "Erro: Tentando atualizar dados da home sem um usuário logado.";
        return;
    }

    // Inicia as requisições de rede. As respostas virão depois, nos slots.
    m_relatorio->obterResumosDoMes(token);
    m_dao->obterRecentes(token, 5);
    m_relatorio->obterHistoricoPatrimonio(token);
}

void pageHome::onResumosRecebidos(double receitas, double despesas)
{
    double saldo = receitas - despesas;

    ui->labelValorReceitas->setText(QString("R$ %1").arg(receitas, 0, 'f', 2));
    ui->labelValorDespesas->setText(QString("R$ %1").arg(despesas, 0, 'f', 2));
    ui->labelSaldoMes->setText(QString("R$ %1").arg(saldo, 0, 'f', 2));

    if (saldo < 0) {
        ui->labelSaldoMes->setStyleSheet("color: #e74c3c;");
    } else {
        ui->labelSaldoMes->setStyleSheet("color: #2ecc71;");
    }

    // Lógica para atualizar o gráfico
    m_chart->removeAllSeries(); // Limpa dados antigos
    m_chart->removeAxis(m_chart->axisX()); // Limpa eixos antigos
    m_chart->removeAxis(m_chart->axisY());

    QBarSet *setReceitas = new QBarSet("Receitas");
    QBarSet *setDespesas = new QBarSet("Despesas");

    // Defina as cores que você quer usar
    setReceitas->setColor(QColor("#2ecc71")); // Verde para receitas
    setDespesas->setColor(QColor("#e74c3c")); // Vermelho para despesas

    *setReceitas << receitas;
    *setDespesas << despesas;

    // Use QBarSeries para um gráfico de barras verticais
    QBarSeries *series = new QBarSeries();
    series->append(setReceitas);
    series->append(setDespesas);

    m_chart->addSeries(series);

    // Configuração do eixo X (categorias)
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append("Mês Atual");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Configuração do eixo Y (valores)
    QValueAxis *axisY = new QValueAxis();
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}

void pageHome::onLancamentosRecentesRecebidos(const QVector<Lancamento>& lancamentos)
{
    ui->tabelaLancamentosRecentes->clearContents();
    ui->tabelaLancamentosRecentes->setRowCount(0);

    for (const auto& lancamento : lancamentos) {
        int linha = ui->tabelaLancamentosRecentes->rowCount();
        ui->tabelaLancamentosRecentes->insertRow(linha);

        // Coluna 0: Data
        QTableWidgetItem *itemData = new QTableWidgetItem(lancamento.data_lancamento.toString("dd/MM/yyyy"));
        ui->tabelaLancamentosRecentes->setItem(linha, 0, itemData);

        // Coluna 1: Descrição
        ui->tabelaLancamentosRecentes->setItem(linha, 1, new QTableWidgetItem(lancamento.descricao));

        // Coluna 2: Valor
        QTableWidgetItem *itemValor = new QTableWidgetItem(QString::number(lancamento.valor, 'f', 2));
        itemValor->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        if (lancamento.tipo == "Receita") {
            itemValor->setForeground(QColor("#2ecc71")); // Verde
        } else {
            itemValor->setForeground(QColor("#e74c3c")); // Vermelho
        }
        ui->tabelaLancamentosRecentes->setItem(linha, 2, itemValor);
    }
    ui->tabelaLancamentosRecentes->blockSignals(false);
}

void pageHome::onErroDeRede(const QString& erro)
{
    QMessageBox::critical(this, "Erro de Rede", "Não foi possível buscar os dados da dashboard:\n" + erro);
}

void pageHome::onHistoricoPatrimonioRecebido(const QVector<HistoricoPatrimonio>& historico)
{
    m_chartPatrimonio->removeAllSeries();
    if(m_chartPatrimonio->axisX()) m_chartPatrimonio->removeAxis(m_chartPatrimonio->axisX());
    if(m_chartPatrimonio->axisY()) m_chartPatrimonio->removeAxis(m_chartPatrimonio->axisY());

    QLineSeries *series = new QLineSeries();
    series->setName("Patrimônio Líquido");

    QStringList categories;
    double minVal = 0, maxVal = 0;

    if (!historico.isEmpty()) {
        minVal = historico.first().valor;
        maxVal = historico.first().valor;
    }

    for (const auto& ponto : historico) {
        series->append(categories.size(), ponto.valor);
        categories << ponto.mes;
        if (ponto.valor < minVal) minVal = ponto.valor;
        if (ponto.valor > maxVal) maxVal = ponto.valor;
    }

    m_chartPatrimonio->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    m_chartPatrimonio->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(minVal, maxVal); // Define o range para melhor visualização
    axisY->setLabelFormat("R$ %.0f");
    m_chartPatrimonio->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    m_chartPatrimonio->legend()->setVisible(true);
    m_chartPatrimonio->legend()->setAlignment(Qt::AlignBottom);
}