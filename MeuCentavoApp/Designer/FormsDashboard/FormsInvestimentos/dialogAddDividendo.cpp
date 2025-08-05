#include "dialogAddDividendo.h"
#include "ui_dialogAddDividendo.h" // Arquivo gerado pelo Qt Designer
#include <QDate>

dialogAddDividendo::dialogAddDividendo(const Ativo& ativo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAddDividendo)
{
    ui->setupUi(this);
    setWindowTitle("Registrar Dividendo/Provento");

    // Guarda o ID do ativo e exibe o ticker na tela (apenas para informação)
    m_idAtivo = ativo.id_ativo;
    ui->lineEditTicker->setText(ativo.ticker);
    ui->lineEditTicker->setReadOnly(true); // O usuário não pode editar o ticker

    // Configurações iniciais dos campos
    ui->dateEditPagamento->setDate(QDate::currentDate());
    ui->spinBoxValorTotal->setMinimum(0.01);
    ui->spinBoxValorTotal->setMaximum(99999999.99);
    
    // Assume que dividendos são em BRL por padrão. Pode ser adaptado se necessário.
    ui->spinBoxValorTotal->setPrefix("R$ ");

    // Conecta os botões "OK" e "Cancelar" às ações padrão do diálogo
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

dialogAddDividendo::~dialogAddDividendo()
{
    delete ui;
}

// Esta função é chamada pela pageInvestimentos após o usuário clicar em "OK"
Dividendo dialogAddDividendo::getDividendo() const
{
    Dividendo novoDividendo;

    // Preenche o objeto com os dados da interface
    novoDividendo.id_ativo = m_idAtivo;
    novoDividendo.data_pagamento = ui->dateEditPagamento->date();
    novoDividendo.valor_total = ui->spinBoxValorTotal->value();
    
    // Os outros campos (id_dividendo, id_usuario) serão preenchidos pelo backend/banco

    return novoDividendo;
}