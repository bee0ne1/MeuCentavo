#include "dialogSimuladorFinanciamento.h"
#include "ui_dialogSimuladorFinanciamento.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h"
#include <QMessageBox>
#include <QLocale>

dialogSimuladorFinanciamento::dialogSimuladorFinanciamento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogSimuladorFinanciamento)
{
    ui->setupUi(this);
    setWindowTitle("Simulador de Financiamento");

    // Configura limites altos para os campos de valor
    ui->spinBoxValorBem->setMaximum(999999999.99);
    ui->spinBoxValorEntrada->setMaximum(999999999.99);
    ui->spinBoxNumParcelas->setMaximum(1200); // Limite de 100 anos

    m_dao = new LancamentoDAO(this);

    // Conecta os sinais do DAO aos slots deste diálogo
    connect(m_dao, &LancamentoDAO::simulacaoFinanciamentoRecebida, this, &dialogSimuladorFinanciamento::onSimulacaoRecebida);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &dialogSimuladorFinanciamento::onErro);
}

dialogSimuladorFinanciamento::~dialogSimuladorFinanciamento()
{
    delete ui;
}

void dialogSimuladorFinanciamento::on_buttonCalcular_clicked()
{
    // Validações básicas da interface
    if (ui->spinBoxValorEntrada->value() >= ui->spinBoxValorBem->value()) {
        QMessageBox::warning(this, "Dados Inválidos", "O valor da entrada deve ser menor que o valor total do bem.");
        return;
    }
    if (ui->spinBoxNumParcelas->value() == 0) {
        QMessageBox::warning(this, "Dados Inválidos", "O número de parcelas não pode ser zero.");
        return;
    }

    ui->buttonCalcular->setEnabled(false);
    ui->buttonCalcular->setText("Calculando...");

    // Coleta os dados dos campos da UI
    double valorBem = ui->spinBoxValorBem->value();
    double valorEntrada = ui->spinBoxValorEntrada->value();
    double taxaJurosAnual = ui->spinBoxTaxaJurosAnual->value();
    int numParcelas = ui->spinBoxNumParcelas->value();
    
    QString token = SessionManager::instance().getToken();

    // Chama o DAO para iniciar a comunicação com o backend
    m_dao->simularFinanciamento(valorBem, valorEntrada, taxaJurosAnual, numParcelas, token);
}

void dialogSimuladorFinanciamento::onSimulacaoRecebida(double valorParcela, double totalPago, double totalJuros)
{
    ui->buttonCalcular->setEnabled(true);
    ui->buttonCalcular->setText("Calcular Financiamento");

    QLocale brLocale(QLocale::Portuguese, QLocale::Brazil);

    // Atualiza os labels de resultado com os valores formatados
    ui->labelValorParcela->setText(brLocale.toCurrencyString(valorParcela));
    ui->labelTotalPago->setText(brLocale.toCurrencyString(totalPago));
    ui->labelTotalJuros->setText(brLocale.toCurrencyString(totalJuros));
}

void dialogSimuladorFinanciamento::onErro(const QString& motivo)
{
    ui->buttonCalcular->setEnabled(true);
    ui->buttonCalcular->setText("Calcular Financiamento");
    QMessageBox::critical(this, "Erro na Simulação", motivo);
}