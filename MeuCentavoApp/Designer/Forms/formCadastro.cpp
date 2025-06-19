#include "formCadastro.h"
#include "ui_formCadastro.h"
#include "formUsuario.h"
#include <QDebug>
#include <QCloseEvent>

formCadastro::formCadastro(formUsuario *usuario,QWidget *parent)
    : QWidget(parent),
      ui(new Ui::formCadastro),
    usuarioWindow(usuario)
{
    ui->setupUi(this);

    connect(ui->lineEditSenha, &QLineEdit::textChanged, this, &formCadastro::verificarCampos);
    connect(ui->lineEditUsuario, &QLineEdit::textChanged, this, &formCadastro::verificarCampos);
    connect(ui->buttonViewPassword, &QPushButton::clicked, this, &formCadastro::visualizarSenha);
    connect(ui->buttonCancelar, &QPushButton::clicked, this, &formCadastro::cancelarCadastro);

}

formCadastro::~formCadastro() {
    delete ui;
}

void formCadastro::closeEvent(QCloseEvent *event) {
    qDebug() << "formCadastro sendo fechado";
    emit cadastroFechado();
    QWidget::closeEvent(event);
}

void formCadastro::verificarCampos() {
    bool usuarioPreenchido = !ui->lineEditUsuario->text().isEmpty();
    bool senhaPreenchida   = !ui->lineEditSenha->text().isEmpty();

    ui->buttonGravarUsuario->setEnabled(usuarioPreenchido && senhaPreenchida);
}

void formCadastro::visualizarSenha() {
    bool senhaEscondida = ui->lineEditSenha->echoMode() == QLineEdit::Password;

    ui->lineEditSenha->setEchoMode(senhaEscondida ? QLineEdit::Normal : QLineEdit::Password);
}

void formCadastro::cancelarCadastro() {
    this->close();
    usuarioWindow->show();
}