//
// Created by bruno on 07/07/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_formMainDashboard.h" resolved

#include "formMainDashboard.h"
#include "ui_formMainDashboard.h"
#include "DataAccess/UsuarioDAO.h"


formMainDashboard::formMainDashboard(const Usuario& usuario, QSqlDatabase db, QWidget *parent) :
    QWidget(parent), ui(new Ui::formMainDashboard),  m_db(db), m_usuario(usuario){
    ui->setupUi(this);
}

formMainDashboard::~formMainDashboard() {
    delete ui;
}
