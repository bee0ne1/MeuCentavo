#include "dialogSimuladorAposentadoria.h"
#include "ui_dialogSimuladorAposentadoria.h"
#include "DataAccess/LancamentoDAO.h"   // Inclui o DAO completo
#include "Gerenciamento/SessionManager.h" // Para pegar o token de autenticação
#include <QMessageBox>
#include <QLocale> // Para formatar os valores em Reais

dialogSimuladorAposentadoria::dialogSimuladorAposentadoria(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogSimuladorAposentadoria)
{
    ui->setupUi(this);
    setWindowTitle("Simulador de Aposentadoria");

    // Instancia o DAO que fará a requisição à API
    m_dao = new LancamentoDAO(this);

    // --- CONEXÕES ---
    // Conecta os sinais do DAO aos nossos slots que tratarão as respostas
    connect(m_dao, &LancamentoDAO::simulacaoAposentadoriaRecebida, this, &dialogSimuladorAposentadoria::onSimulacaoRecebida);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &dialogSimuladorAposentadoria::onErro);
}

dialogSimuladorAposentadoria::~dialogSimuladorAposentadoria()
{
    delete ui;
}

void dialogSimuladorAposentadoria::on_buttonCalcular_clicked()
{
    // 1. Validação dos dados de entrada
    if (ui->spinBoxIdadeAtual->value() >= ui->spinBoxIdadeAposentadoria->value()) {
        QMessageBox::warning(this, "Dados Inválidos", "A idade para aposentadoria deve ser maior que a idade atual.");
        return;
    }

    // Desabilita o botão para evitar cliques duplos e informa o usuário
    ui->buttonCalcular->setEnabled(false);
    ui->buttonCalcular->setText("Calculando...");

    // 2. Coleta os dados da interface
    int idadeAtual = ui->spinBoxIdadeAtual->value();
    int idadeAposentadoria = ui->spinBoxIdadeAposentadoria->value();
    double saldoInicial = ui->spinBoxSaldoInicial->value();
    double aporteMensal = ui->spinBoxAporteMensal->value();
    double rentabilidadeAnual = ui->spinBoxRentabilidadeAnual->value();
    
    QString token = SessionManager::instance().getToken();

    // 3. Chama o método do DAO para iniciar a simulação no backend
    m_dao->simularAposentadoria(idadeAtual, idadeAposentadoria, saldoInicial, aporteMensal, rentabilidadeAnual, token);
}

void dialogSimuladorAposentadoria::onSimulacaoRecebida(double valorFinal, double totalInvestido, double jurosTotais)
{
    // Reabilita o botão
    ui->buttonCalcular->setEnabled(true);
    ui->buttonCalcular->setText("Calcular Projeção");

    // Formata os valores para exibição como moeda local (BRL)
    QLocale brLocale(QLocale::Portuguese, QLocale::Brazil);

    // Atualiza os labels de resultado na interface
    ui->labelValorFinal->setText(brLocale.toCurrencyString(valorFinal));
    ui->labelTotalInvestido->setText(brLocale.toCurrencyString(totalInvestido));
    ui->labelJurosTotais->setText(brLocale.toCurrencyString(jurosTotais));
}

void dialogSimuladorAposentadoria::onErro(const QString& motivo)
{
    // Reabilita o botão e exibe o erro
    ui->buttonCalcular->setEnabled(true);
    ui->buttonCalcular->setText("Calcular Projeção");
    QMessageBox::critical(this, "Erro na Simulação", motivo);
}