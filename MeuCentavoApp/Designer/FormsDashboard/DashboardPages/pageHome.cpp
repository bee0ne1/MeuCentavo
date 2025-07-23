#include "pageHome.h"
#include "ui_pageHome.h"
#include "DataAccess/LancamentoDAO.h"
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
    m_chart = new QChart();
    m_chart->setTitle("Resumo Mensal");
    m_chart->setTheme(QChart::ChartThemeDark);
    m_chart->setAnimationOptions(QChart::SeriesAnimations);

    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumHeight(250);

    // Conecta os sinais de resultado do DAO aos nossos slots
    connect(m_dao, &LancamentoDAO::resumosRecebidos, this, &pageHome::onResumosRecebidos);
    connect(m_dao, &LancamentoDAO::lancamentosRecebidos, this, &pageHome::onLancamentosRecentesRecebidos);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &pageHome::onErroDeRede);

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
    m_dao->obterResumosDoMes(token);
    m_dao->obterRecentes(token, 5);
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