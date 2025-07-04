//
// Created by bruno on 18/06/25.
//

#ifndef FORMUSUARIO_H
#define FORMUSUARIO_H

#include <QWidget>
#include <QSqlDatabase>
#include "Modelo/Usuario.h"

class formCadastro;
class formExcluirUsuario;

QT_BEGIN_NAMESPACE
namespace Ui { class formUsuario; }
QT_END_NAMESPACE

class formUsuario : public QWidget {
Q_OBJECT

public:
    explicit formUsuario(QSqlDatabase db, QWidget *parent = nullptr);
    ~formUsuario() override;

signals:
    void usuarioFechado();
    void usuarioAtual(const Usuario& usuario);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::formUsuario *ui;
    formCadastro* cadastroWindow = nullptr;
    formExcluirUsuario* excluirWindow = nullptr;
     QSqlDatabase m_db;

private slots:
    void abrirFormCadastro();
    void voltarFormInicio();
    void carregarListaDeUsuarios();
    void abrirExcluirUsuarios();
};



#endif //FORMUSUARIO_H
