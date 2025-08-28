#include "dialogSimuladorCambio.h"
#include "ui_dialogSimuladorCambio.h"
#include "DataAccess/RelatorioDAO.h"
#include "Gerenciamento/SessionManager.h"
#include <QMessageBox>
#include <QLocale>

dialogSimuladorCambio::dialogSimuladorCambio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogSimuladorCambio)
{
    ui->setupUi(this);
    setWindowTitle("Simulador de Câmbio");

    m_dao = new RelatorioDAO(this);
    popularComboBoxes();

    connect(m_dao, &RelatorioDAO::simulacaoCambioRecebida, this, &dialogSimuladorCambio::onSimulacaoRecebida);
    connect(m_dao, &RelatorioDAO::onRelatorioError, this, &dialogSimuladorCambio::onErro);
}

dialogSimuladorCambio::~dialogSimuladorCambio()
{
    delete ui;
}

void dialogSimuladorCambio::popularComboBoxes()
{
    // Adiciona as moedas que o backend suporta
    ui->comboMoedaOrigem->addItem("Real Brasileiro (BRL)", "BRL");
    ui->comboMoedaOrigem->addItem("Dólar Americano (USD)", "USD");
    ui->comboMoedaOrigem->addItem("Euro (EUR)", "EUR");

    ui->comboMoedaDestino->addItem("Real Brasileiro (BRL)", "BRL");
    ui->comboMoedaDestino->addItem("Dólar Americano (USD)", "USD");
    ui->comboMoedaDestino->addItem("Euro (EUR)", "EUR");

    // Pré-seleciona uma conversão comum
    ui->comboMoedaOrigem->setCurrentIndex(1); // USD
    ui->comboMoedaDestino->setCurrentIndex(0); // BRL
}

void dialogSimuladorCambio::on_buttonConverter_clicked()
{
    double valor = ui->spinBoxValor->value();
    if (valor <= 0) {
        QMessageBox::warning(this, "Valor Inválido", "Por favor, insira um valor maior que zero para converter.");
        return;
    }

    ui->buttonConverter->setEnabled(false);
    ui->buttonConverter->setText("Convertendo...");
    
    QString moedaOrigem = ui->comboMoedaOrigem->currentData().toString();
    QString moedaDestino = ui->comboMoedaDestino->currentData().toString();
    QString token = SessionManager::instance().getToken();

    m_dao->simularCambio(moedaOrigem, moedaDestino, valor, token);
}

void dialogSimuladorCambio::onSimulacaoRecebida(double valorConvertido)
{
    ui->buttonConverter->setEnabled(true);
    ui->buttonConverter->setText("Converter");

    // Formata o resultado com base na moeda de DESTINO
    QLocale locale = QLocale(QLocale::Portuguese, QLocale::Brazil); // Padrão BRL
    QString simbolo = "R$";

    QString moedaDestino = ui->comboMoedaDestino->currentData().toString();
    if (moedaDestino == "USD") {
        locale = QLocale(QLocale::English, QLocale::UnitedStates);
        simbolo = "$";
    } else if (moedaDestino == "EUR") {
        locale = QLocale(QLocale::German, QLocale::Germany); // Euro
        simbolo = "€";
    }

    ui->labelResultado->setText(QString("%1 %2").arg(simbolo).arg(valorConvertido, 0, 'f', 2));
}

void dialogSimuladorCambio::onErro(const QString& motivo)
{
    ui->buttonConverter->setEnabled(true);
    ui->buttonConverter->setText("Converter");
    QMessageBox::critical(this, "Erro de Conversão", motivo);
}