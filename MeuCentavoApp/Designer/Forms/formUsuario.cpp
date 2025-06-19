//
// Created by bruno on 18/06/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_formUsuario.h" resolved

#include "formUsuario.h"
#include "Designer/formMain.h"
#include "ui_formUsuario.h"
#include "formCadastro.h"
#include <QDebug>

formUsuario::formUsuario(formMain *inicio, QWidget *parent) :
    QWidget(parent), ui(new Ui::formUsuario), inicioWindow(inicio) {
    ui->setupUi(this);
    connect(ui->buttonCadastro, &QPushButton::clicked, this, &formUsuario::abrirFormCadastro);
    connect(ui->buttonBack, &QPushButton::clicked, this, &formUsuario::voltarFormInicio);

}

formUsuario::~formUsuario() {
    delete ui;
}

void formUsuario::closeEvent(QCloseEvent *event)
{
    emit usuarioFechado();
    QWidget::closeEvent(event);
}

void formUsuario::abrirFormCadastro() {
        if (!cadastroWindow) {
            cadastroWindow = new formCadastro(this);

            connect(cadastroWindow, &formCadastro::cadastroFechado, this, &formUsuario::show);
        }

        this->hide();
        cadastroWindow->show();
}

void formUsuario::voltarFormInicio() {
    this->close();
    if (inicioWindow)
        inicioWindow->show();
}
