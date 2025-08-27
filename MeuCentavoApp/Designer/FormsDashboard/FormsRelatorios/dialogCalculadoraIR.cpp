#include "dialogCalculadoraIR.h"
#include "ui_dialogCalculadoraIR.h"
#include "Gerenciamento/SessionManager.h"
#include <QMessageBox>
#include <QLocale>
#include <QDate>

dialogCalculadoraIR::dialogCalculadoraIR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogCalculadoraIR)
{
    ui->setupUi(this);
    setWindowTitle("Calculadora de IR (Ações - Swing Trade)");

    m_dao = new LancamentoDAO(this);
    popularCamposData();

    connect(m_dao, &LancamentoDAO::calculoIRRecebido, this, &dialogCalculadoraIR::onCalculoRecebido);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &dialogCalculadoraIR::onErro);
}

dialogCalculadoraIR::~dialogCalculadoraIR()
{
    delete ui;
}

void dialogCalculadoraIR::popularCamposData()
{
    for (int i = 1; i <= 12; ++i) {
        ui->comboMes->addItem(QLocale::system().monthName(i), i);
    }
    
    int anoAtual = QDate::currentDate().year();
    ui->spinBoxAno->setRange(2020, anoAtual);
    ui->spinBoxAno->setValue(anoAtual);
    ui->comboMes->setCurrentIndex(QDate::currentDate().month() - 1);
}

void dialogCalculadoraIR::on_buttonCalcular_clicked()
{
    ui->buttonCalcular->setEnabled(false);
    ui->buttonCalcular->setText("Calculando...");

    int mes = ui->comboMes->currentData().toInt();
    int ano = ui->spinBoxAno->value();
    QString token = SessionManager::instance().getToken();

    m_dao->calcularIRsobreAcoes(mes, ano, token);
}

void dialogCalculadoraIR::onCalculoRecebido(const ResultadoIR& resultado)
{
    ui->buttonCalcular->setEnabled(true);
    ui->buttonCalcular->setText("Calcular Imposto");

    QLocale brLocale(QLocale::Portuguese, QLocale::Brazil);

    ui->labelTotalVendas->setText("Total de Vendas no Mês: " + brLocale.toCurrencyString(resultado.totalVendas));
    
    QString lucroTexto = (resultado.lucroApurado >= 0) ? "Lucro Apurado: " : "Prejuízo Apurado: ";
    ui->labelLucroApurado->setText(lucroTexto + brLocale.toCurrencyString(qAbs(resultado.lucroApurado)));
    
    if (resultado.isento) {
        ui->labelIsencao->setText("Resultado: ISENTO (Vendas abaixo de R$ 20.000,00)");
        ui->labelIsencao->setStyleSheet("color: #2ecc71;"); // Verde
    } else {
        ui->labelIsencao->setText("Resultado: NÃO ISENTO (Vendas acima de R$ 20.000,00)");
         ui->labelIsencao->setStyleSheet(""); // Cor padrão
    }

    ui->labelImpostoDevido->setText("Imposto Devido (DARF): " + brLocale.toCurrencyString(resultado.impostoDevido));
}

void dialogCalculadoraIR::onErro(const QString& motivo)
{
    ui->buttonCalcular->setEnabled(true);
    ui->buttonCalcular->setText("Calcular Imposto");
    QMessageBox::critical(this, "Erro no Cálculo", motivo);
}