//
// Created by bruno on 10/07/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_pageRelatorios.h" resolved

#include "pageRelatorios.h"
#include "ui_pageRelatorios.h"


pageRelatorios::pageRelatorios(const Usuario& usuario, QSqlDatabase db, QWidget *parent) :
    QWidget(parent), ui(new Ui::pageRelatorios),m_db(db),m_usuarioAtual(usuario) {
    ui->setupUi(this);
}

pageRelatorios::~pageRelatorios() {
    delete ui;
}
