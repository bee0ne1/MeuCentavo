//
// Created by bruno on 18/06/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_formUsuario.h" resolved

#include "formUsuario.h"
#include "Designer/formMain.h"
#include "ui_formUsuario.h"
#include "formCadastro.h"
#include <QDebug>

formUsuario::formUsuario(QSqlDatabase db, QWidget *parent) :
    QWidget(parent), ui(new Ui::formUsuario), m_db(db) { // A conexão recebida é guardada aqui!
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
            cadastroWindow = new formCadastro(this,m_db);

            connect(cadastroWindow, &formCadastro::cadastroFechado, this, &formUsuario::show);
        }

        this->hide();
        cadastroWindow->show();
}

void formUsuario::voltarFormInicio()
{
    // Não precisamos mais guardar um ponteiro para a janela de início.
    // Simplesmente fechamos esta janela. O 'closeEvent' acima emitirá o sinal
    // 'usuarioFechado', e o 'formMain' que está escutando esse sinal irá
    // se encarregar de aparecer novamente. É um design mais limpo!
    this->close();
}
