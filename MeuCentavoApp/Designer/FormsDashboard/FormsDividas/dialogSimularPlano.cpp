#include "dialogSimularPlano.h"
#include "ui_dialogSimularPlano.h"
#include "Gerenciamento/SessionManager.h"
#include "DataAccess/RelatorioDAO.h"
#include <QMessageBox>
#include <QLocale>

dialogSimularPlano::dialogSimularPlano(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogSimularPlano)
{
    ui->setupUi(this);
    setWindowTitle("Planejamento de Quitação de Dívidas");

    // Instancia o DAO para fazer a requisição à API
    m_dao = new RelatorioDAO(this);

    // Configura a tabela de resultados
    ui->tableResultadoSimulacao->setColumnCount(4);
    ui->tableResultadoSimulacao->setHorizontalHeaderLabels({"Mês", "Dívida Foco", "Pagamento Extra", "Saldo Restante"});
    ui->tableResultadoSimulacao->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableResultadoSimulacao->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Conecta os sinais do DAO aos slots deste diálogo
    connect(m_dao, &RelatorioDAO::planoSimuladoRecebido, this, &dialogSimularPlano::onPlanoRecebido);
    connect(m_dao, &RelatorioDAO::onRelatorioError, this, &dialogSimularPlano::onErro);
}

dialogSimularPlano::~dialogSimularPlano()
{
    delete ui;
}

void dialogSimularPlano::on_buttonSimularPlano_clicked()
{
    double valorExtra = ui->spinBoxValorExtra->value();
    if (valorExtra <= 0) {
        QMessageBox::warning(this, "Valor Inválido", "Por favor, insira um valor extra mensal maior que zero.");
        return;
    }

    // Desabilita o botão para evitar cliques duplos e informa o usuário
    ui->buttonSimularPlano->setEnabled(false);
    ui->buttonSimularPlano->setText("Simulando...");

    // Pega o texto completo, ex: "Avalanche (maior juro)"
    QString textoSelecionado = ui->comboEstrategia->currentText();
    QString estrategia;
    // Extrai a palavra-chave que a API espera
    if (textoSelecionado.startsWith("Avalanche")) {
        estrategia = "Avalanche";
    } else {
        estrategia = "Bola de Neve";
    }

    QString token = SessionManager::instance().getToken();

    qDebug() << "Estratégia selecionada no frontend:" << estrategia;

    // Chama a função do DAO para iniciar a simulação
    m_dao->simularPlanoQuitacao(valorExtra, estrategia, token);
}

void dialogSimularPlano::onPlanoRecebido(const QVector<LinhaCronograma>& cronograma, int mesesTotais)
{
    // Reabilita o botão
    ui->buttonSimularPlano->setEnabled(true);
    ui->buttonSimularPlano->setText("Simular Plano");

    // Exibe um resumo do resultado (opcional, mas recomendado)
    ui->labelResultadoResumo->setText(QString("Plano de quitação completo em %1 meses!").arg(mesesTotais));
    
    // Popula a tabela com o cronograma
    ui->tableResultadoSimulacao->setRowCount(0);
    QLocale brLocale(QLocale::Portuguese, QLocale::Brazil);

    for (const auto& linha : cronograma) {
        int row = ui->tableResultadoSimulacao->rowCount();
        ui->tableResultadoSimulacao->insertRow(row);

        ui->tableResultadoSimulacao->setItem(row, 0, new QTableWidgetItem(QString::number(linha.mes)));
        ui->tableResultadoSimulacao->setItem(row, 1, new QTableWidgetItem(linha.nomeDivida));
        ui->tableResultadoSimulacao->setItem(row, 2, new QTableWidgetItem(brLocale.toCurrencyString(linha.valorPago)));
        ui->tableResultadoSimulacao->setItem(row, 3, new QTableWidgetItem(brLocale.toCurrencyString(linha.saldoRestante)));
    }
}

void dialogSimularPlano::onErro(const QString& motivo)
{
    // Reabilita o botão e exibe o erro
    ui->buttonSimularPlano->setEnabled(true);
    ui->buttonSimularPlano->setText("Simular Plano");
    QMessageBox::critical(this, "Erro na Simulação", motivo);
}