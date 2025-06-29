#include "formMain.h"
#include "ui_formMain.h"
#include "Forms/formUsuario.h"  // Inclui as definições das janelas que vai abrir
#include <QDebug>

formMain::formMain(QSqlDatabase db, QWidget *parent):
    QMainWindow(parent), ui(new Ui::formMain), m_db(db) {
    ui->setupUi(this);
    connect(ui->buttonSwitchUsuario, &QPushButton::clicked, this, &formMain::abrirTelaUsuario);
    connect(ui->buttonExit, &QPushButton::clicked, this, &QApplication::quit);
}

formMain::~formMain() {
    delete ui;
}


void formMain::abrirTelaUsuario() {

    if (!usuarioWindow) {
        usuarioWindow = new formUsuario(m_db, nullptr);

        connect(usuarioWindow, &formUsuario::usuarioFechado, this, &formMain::show);
    }

    this->hide();
    usuarioWindow->show();
}
