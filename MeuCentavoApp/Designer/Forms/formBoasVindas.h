//
// Created by bruno on 04/07/25.
//

#ifndef FORMBOASVINDAS_H
#define FORMBOASVINDAS_H

#include <QWidget>
#include <QSqlDatabase>

class formCadastro;

namespace Ui {
    class formBoasVindas;
}

class formBoasVindas : public QWidget
{
    Q_OBJECT

public:
    explicit formBoasVindas(QSqlDatabase db, QWidget *parent = nullptr);
    ~formBoasVindas();

private slots:
    void abrirTelaCadastro();
    void onCadastroConcluido();

private:
    Ui::formBoasVindas *ui;
    QSqlDatabase m_db;
    formCadastro* m_formCadastro;
};

#endif // FORMBOASVINDAS_H