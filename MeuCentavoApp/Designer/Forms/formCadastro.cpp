#include "formCadastro.h"
#include "ui_formCadastro.h"
#include <QDebug>
#include <QCloseEvent>

formCadastro::formCadastro(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::formCadastro)
{
    ui->setupUi(this);
    qDebug() << "formCadastro construído";
}

formCadastro::~formCadastro() {
    qDebug() << "formCadastro destruído";
    delete ui;
}

void formCadastro::closeEvent(QCloseEvent *event) {
    qDebug() << "formCadastro sendo fechado";
    emit cadastroFechado();
    QWidget::closeEvent(event);
}
