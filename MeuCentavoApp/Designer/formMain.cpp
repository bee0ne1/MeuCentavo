#include "formMain.h"
#include "ui_formMain.h"
#include <QDebug>

formMain::formMain(QWidget *parent):
    QMainWindow(parent), ui(new Ui::formMain) {
    ui->setupUi(this);
    connect(ui->buttonSwitchUsuario, &QPushButton::clicked, this, &formMain::abrirTelaUsuario);
    connect(ui->buttonExit, &QPushButton::clicked, this, &QApplication::quit);
}

formMain::~formMain() {
    delete ui;
}


void formMain::abrirTelaUsuario() {

    if (!usuarioWindow) {
        usuarioWindow = new formUsuario(this);

        connect(usuarioWindow, &formUsuario::usuarioFechado, this, &formMain::show);
    }

    this->hide();
    usuarioWindow->show();
}
