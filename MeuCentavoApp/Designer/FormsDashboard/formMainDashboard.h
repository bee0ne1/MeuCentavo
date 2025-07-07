//
// Created by bruno on 07/07/25.
//

#ifndef FORMMAINDASHBOARD_H
#define FORMMAINDASHBOARD_H

#include <QWidget>
#include <QSqlDatabase>
#include "Modelo/Usuario.h"


QT_BEGIN_NAMESPACE
namespace Ui { class formMainDashboard; }
QT_END_NAMESPACE

class formMainDashboard : public QWidget {
Q_OBJECT

public:
    explicit formMainDashboard(const Usuario& usuario, QSqlDatabase db,QWidget *parent = nullptr);
    ~formMainDashboard() override;

private:
    Ui::formMainDashboard *ui;
    QSqlDatabase m_db;
    Usuario m_usuario;

};


#endif //FORMMAINDASHBOARD_H
