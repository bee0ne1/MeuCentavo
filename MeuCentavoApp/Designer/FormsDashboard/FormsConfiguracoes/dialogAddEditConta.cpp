#include "dialogAddEditConta.h"
#include "ui_dialogAddEditConta.h"

DialogAddEditConta::DialogAddEditConta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddEditConta)
{
    ui->setupUi(this);
    setWindowTitle("Adicionar/Editar Conta");
    m_idConta = -1; // -1 indica que é uma nova conta por defeito

    // Preenche o ComboBox de tipos com algumas opções padrão
    ui->comboBoxTipo->addItems({"Conta Corrente", "Poupança", "Cartão de Crédito", "Investimentos", "Dinheiro", "Outros"});

    ui->comboMoeda->addItem("Real Brasileiro (BRL)", "BRL");
    ui->comboMoeda->addItem("Dólar Americano (USD)", "USD");
    ui->comboMoeda->addItem("Euro (EUR)", "EUR");

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

}

DialogAddEditConta::~DialogAddEditConta()
{
    delete ui;
}

// Esta função é chamada quando queremos EDITAR uma conta.
// Ela preenche os campos com os dados da conta existente.
void DialogAddEditConta::setConta(const Conta& conta)
{
    setWindowTitle("Editar Conta");
    m_idConta = conta.id; // Guarda o ID
    ui->lineEditNome->setText(conta.nome);
    ui->comboBoxTipo->setCurrentText(conta.tipo_conta);
    ui->spinBoxSaldo->setValue(conta.saldo_inicial);

    int index = ui->comboMoeda->findData(conta.moeda_codigo);
    if (index != -1) { // -1 significa que não encontrou
        ui->comboMoeda->setCurrentIndex(index);
    }
}

// Esta função é chamada depois que o usuário clica em "OK".
// Ela coleta os dados da UI e os retorna num objeto Conta.
Conta DialogAddEditConta::getConta() const
{
    Conta c;
    c.id = m_idConta; // Terá o ID da conta (-1 se for nova)
    c.nome = ui->lineEditNome->text();
    c.tipo_conta = ui->comboBoxTipo->currentText();
    c.saldo_inicial = ui->spinBoxSaldo->value();
    c.moeda_codigo = ui->comboMoeda->currentData().toString();
    return c;
}