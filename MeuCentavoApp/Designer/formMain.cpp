#include "formMain.h"
#include "ui_formMain.h"
#include <QDebug>

formMain::formMain(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::formMain),
      cadastroWindow(nullptr)
{
    ui->setupUi(this);

    connect(ui->buttonCadastro, &QPushButton::clicked, this, &formMain::abrirTelaCadastro);
}

formMain::~formMain() {
    delete ui;
}

void formMain::abrirTelaCadastro() {
    qDebug() << "Abrindo tela de cadastro";

    if (!cadastroWindow) {
        cadastroWindow = new formCadastro();  // sem parent!

        connect(cadastroWindow, &formCadastro::cadastroFechado, this, &formMain::show);
        qDebug() << "Nova formCadastro criada";
    }

    this->hide();
    cadastroWindow->show();
}
