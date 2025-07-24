#include "dialogAddEditMeta.h"
#include "ui_dialogAddEditMeta.h"
#include <QMessageBox>
dialogAddEditMeta::dialogAddEditMeta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAddEditMeta)
{
    ui->setupUi(this);
    setWindowTitle("Adicionar Meta");
    m_idMeta = -1; // -1 indica o modo "Adicionar"

    ui->spinBoxValorAlvo->setMinimum(0.01);
    ui->spinBoxValorAlvo->setMaximum(999999999.99);
    // Define a data do widget para a data atual do sistema.
    ui->dateEditDataAlvo->setDate(QDate::currentDate());

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

}

dialogAddEditMeta::~dialogAddEditMeta()
{
    delete ui;
}

void dialogAddEditMeta::setMeta(const Meta& meta)
{
    setWindowTitle("Editar Meta");
    m_idMeta = meta.id_meta;
    ui->lineEditNome->setText(meta.nome);
    ui->spinBoxValorAlvo->setValue(meta.valor_alvo);
    if (meta.data_alvo.isValid()) {
        ui->dateEditDataAlvo->setDate(meta.data_alvo);
    }
}

Meta dialogAddEditMeta::getMeta() const
{
    Meta meta;
    meta.id_meta = m_idMeta;
    meta.nome = ui->lineEditNome->text();
    meta.valor_alvo = ui->spinBoxValorAlvo->value();
    meta.data_alvo = ui->dateEditDataAlvo->date();
    // O valor_atual será gerenciado em outro lugar
    meta.valor_atual = 0; 
    return meta;
}

void dialogAddEditMeta::accept()
{
    QDate dataSelecionada = ui->dateEditDataAlvo->date();
    QDate dataAtual = QDate::currentDate();

    // Validação: a data selecionada não pode ser anterior à data atual
    if (dataSelecionada < dataAtual) {
        QMessageBox::warning(this, "Data Inválida", "A data alvo da meta não pode ser anterior ao dia de hoje.");
        return; // Impede que a janela seja fechada
    }

    // Se a data for válida, executa o comportamento padrão de "accept", que fecha a janela com sucesso.
    QDialog::accept();
}
