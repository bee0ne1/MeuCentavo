//
// Created by bruno on 10/07/25.
//

#ifndef PAGERELATORIOS_H
#define PAGERELATORIOS_H

#include <QWidget>
#include <QSqlDatabase>
#include "Modelo/Usuario.h"

QT_BEGIN_NAMESPACE
namespace Ui { class pageRelatorios; }
QT_END_NAMESPACE

class pageRelatorios : public QWidget {
Q_OBJECT

public:
    explicit pageRelatorios(const Usuario& usuario, QSqlDatabase db,QWidget *parent = nullptr);
    ~pageRelatorios() override;

private:
    Ui::pageRelatorios *ui;
    QSqlDatabase m_db;
    Usuario m_usuarioAtual;
};


#endif //PAGERELATORIOS_H
