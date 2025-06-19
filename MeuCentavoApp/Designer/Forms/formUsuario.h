//
// Created by bruno on 18/06/25.
//

#ifndef FORMUSUARIO_H
#define FORMUSUARIO_H

#include <QWidget>
#include "formCadastro.h"

class formMain;


QT_BEGIN_NAMESPACE
namespace Ui { class formUsuario; }
QT_END_NAMESPACE

class formUsuario : public QWidget {
Q_OBJECT

public:
    explicit formUsuario(formMain *inicio,QWidget *parent = nullptr);
    ~formUsuario() override;

signals:
    void usuarioFechado();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::formUsuario *ui;
    formCadastro* cadastroWindow = nullptr;
    formMain* inicioWindow = nullptr;

private slots:
    void abrirFormCadastro();
    void voltarFormInicio();
};



#endif //FORMUSUARIO_H
