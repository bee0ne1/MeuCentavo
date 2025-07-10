//
// Created by bruno on 10/07/25.
//

#ifndef PAGEHOME_H
#define PAGEHOME_H

#include <QWidget>
#include <QSqlDatabase>
#include "Modelo/Usuario.h"

QT_BEGIN_NAMESPACE
namespace Ui { class pageHome; }
QT_END_NAMESPACE

class pageHome : public QWidget {
Q_OBJECT

public:
    explicit pageHome(const Usuario& usuario, QSqlDatabase db,QWidget *parent = nullptr);
    ~pageHome() override;

private:
    Ui::pageHome *ui;
    QSqlDatabase m_db;
    Usuario m_usuarioAtual;
};


#endif //PAGEHOME_H
