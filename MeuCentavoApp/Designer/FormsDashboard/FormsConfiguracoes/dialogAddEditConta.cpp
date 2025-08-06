#include "dialogAddEditConta.h"
#include "ui_dialogAddEditConta.h"
#include <QMessageBox> // Para a janela de aviso
#include <QDate>       // Para pegar a data atual

DialogAddEditConta::DialogAddEditConta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddEditConta)
{
    ui->setupUi(this);
    setWindowTitle("Adicionar/Editar Conta");
    m_idConta = -1; // -1 indica que é uma nova conta por defeito

    ui->comboMoeda->addItem("Real Brasileiro (BRL)", "BRL");
    ui->comboMoeda->addItem("Dólar Americano (USD)", "USD");
    ui->comboMoeda->addItem("Euro (EUR)", "EUR");

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    // --- LÓGICA DE VISIBILIDADE (CONEXÃO) ---
    // Conecta a mudança do ComboBox de Tipo ao nosso novo slot
    connect(ui->comboBoxTipo, &QComboBox::currentTextChanged, this, &DialogAddEditConta::onTipoContaChanged);

    // Chama a função uma vez no início para garantir o estado visual correto
    onTipoContaChanged(ui->comboBoxTipo->currentText());

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

    // --- PREENCHE OS NOVOS CAMPOS SE FOREM UMA DÍVIDA ---
    onTipoContaChanged(conta.tipo_conta); // Garante que o groupBox apareça se for uma dívida
    if (ui->groupBoxDivida->isVisible()) {
        ui->spinBoxJuros->setValue(conta.taxa_juros);
        ui->spinBoxValorTotalDivida->setValue(conta.valor_total_divida);
        if (conta.data_vencimento.isValid()) {
            ui->dateEditVencimento->setDate(conta.data_vencimento);
        }
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

    // --- COLETA OS DADOS DOS NOVOS CAMPOS SE FOREM UMA DÍVIDA ---
    if (ui->groupBoxDivida->isVisible()) {
        c.taxa_juros = ui->spinBoxJuros->value();
        c.valor_total_divida = ui->spinBoxValorTotalDivida->value();
        c.data_vencimento = ui->dateEditVencimento->date();
    } else {
        // Garante que os campos sejam nulos se não for uma dívida
        c.taxa_juros = 0;
        c.valor_total_divida = 0;
        c.data_vencimento = QDate();
    }

    return c;
}

// função para controlar a visibilidade dos campos de dívida
void DialogAddEditConta::onTipoContaChanged(const QString& tipo)
{
    bool isDivida = (tipo == "Financiamento" || tipo == "Empréstimo" || tipo == "Cartão de Crédito");
    ui->groupBoxDivida->setVisible(isDivida);
}

void DialogAddEditConta::accept()
{
    // Verificação 1: A validação só se aplica se os campos de dívida estiverem visíveis
    if (ui->groupBoxDivida->isVisible()) {
        QDate dataVencimento = ui->dateEditVencimento->date();
        QDate dataAtual = QDate::currentDate();

        // Verificação 2: A data de vencimento não pode ser anterior ao dia de hoje
        if (dataVencimento < dataAtual) {
            QMessageBox::warning(this, "Data Inválida",
                                 "A data de vencimento da dívida não pode ser anterior ao dia de hoje.");
            return; // Impede que a janela seja fechada, dando ao usuário a chance de corrigir
        }
    }

    // Se todas as validações passarem, executa o comportamento padrão do "accept",
    // que é fechar a janela com sucesso.
    QDialog::accept();
}