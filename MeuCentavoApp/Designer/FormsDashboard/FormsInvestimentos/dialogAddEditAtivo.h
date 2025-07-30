#ifndef DIALOGADDEDITATIVO_H
#define DIALOGADDEDITATIVO_H

#include <QDialog>
#include "Modelo/Ativo.h"

namespace Ui {
    class dialogAddEditAtivo;
}

class dialogAddEditAtivo : public QDialog
{
    Q_OBJECT

public:
    explicit dialogAddEditAtivo(QWidget *parent = nullptr);
    ~dialogAddEditAtivo();

    void setAtivo(const Ativo& ativo);
    Ativo getAtivo() const;

private:
    void popularComboBoxTipos();

    Ui::dialogAddEditAtivo *ui;
    int m_idAtivo;
};

#endif // DIALOGADDEDITATIVO_H