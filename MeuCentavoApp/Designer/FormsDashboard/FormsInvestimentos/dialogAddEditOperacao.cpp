#include "dialogAddEditOperacao.h"
#include "ui_dialogAddEditOperacao.h"

dialogAddEditOperacao::dialogAddEditOperacao(const Ativo& ativo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAddEditOperacao)
{
    ui->setupUi(this);
    setWindowTitle("Registrar Nova Operação");
    m_idAtivo = ativo.id_ativo;

    // Preenche o ticker e o desabilita, pois ele é apenas informativo
    ui->lineEditTicker->setText(ativo.ticker);

    // Configura os campos
    ui->comboBoxTipoOperacao->addItems({"Compra", "Venda"});
    ui->dateEditData->setDate(QDate::currentDate());
    ui->spinBoxQuantidade->setDecimals(8); // Para criptomoedas
    ui->spinBoxQuantidade->setMaximum(999999999.99);
    ui->spinBoxPreco->setDecimals(5);
    ui->spinBoxPreco->setMaximum(999999999.99);
    ui->spinBoxCustos->setMaximum(999999999.99);

    // Conecta os botões OK e Cancelar
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

dialogAddEditOperacao::~dialogAddEditOperacao()
{
    delete ui;
}

OperacaoInvestimento dialogAddEditOperacao::getOperacao() const
{
    OperacaoInvestimento op;
    op.id_ativo = m_idAtivo;
    op.tipo_operacao = ui->comboBoxTipoOperacao->currentText();
    op.data_operacao = ui->dateEditData->date();
    op.quantidade = ui->spinBoxQuantidade->value();
    op.preco_unitario = ui->spinBoxPreco->value();
    op.custos = ui->spinBoxCustos->value();
    return op;
}