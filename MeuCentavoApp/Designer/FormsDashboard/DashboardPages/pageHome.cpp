//
// Created by bruno on 10/07/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_pageHome.h" resolved

#include "pageHome.h"
#include "ui_pageHome.h"


pageHome::pageHome(const Usuario& usuario, QSqlDatabase db,QWidget *parent) :
    QWidget(parent), ui(new Ui::pageHome) {
    ui->setupUi(this);
}

pageHome::~pageHome() {
    delete ui;
}
