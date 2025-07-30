#include "dialogAddEditAtivo.h"
#include "ui_dialogAddEditAtivo.h"

dialogAddEditAtivo::dialogAddEditAtivo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAddEditAtivo)
{
    ui->setupUi(this);
    setWindowTitle("Adicionar Ativo");
    m_idAtivo = -1; // Modo "Adicionar"

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    popularComboBoxTipos();
}

dialogAddEditAtivo::~dialogAddEditAtivo()
{
    delete ui;
}

void dialogAddEditAtivo::popularComboBoxTipos()
{
    // Você pode expandir esta lista conforme sua necessidade
    ui->comboBoxTipoAtivo->addItems({
        "Ação",
        "FII",
        "ETF",
        "BDR",
        "Criptomoeda",
        "Tesouro Direto",
        "Outros"
    });
}

void dialogAddEditAtivo::setAtivo(const Ativo& ativo)
{
    setWindowTitle("Editar Ativo");
    m_idAtivo = ativo.id_ativo;
    ui->lineEditTicker->setText(ativo.ticker);
    ui->lineEditTicker->setEnabled(false); // O ticker não deve ser editável
    ui->lineEditNome->setText(ativo.nome);
    ui->comboBoxTipoAtivo->setCurrentText(ativo.tipo_ativo);
}

Ativo dialogAddEditAtivo::getAtivo() const
{
    Ativo ativo;
    ativo.id_ativo = m_idAtivo;
    ativo.ticker = ui->lineEditTicker->text();
    ativo.nome = ui->lineEditNome->text();
    ativo.tipo_ativo = ui->comboBoxTipoAtivo->currentText();
    return ativo;
}