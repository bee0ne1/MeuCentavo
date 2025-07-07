//
// Created by bruno on 07/07/25.
//

#ifndef FORMLOGINSENHA_H
#define FORMLOGINSENHA_H

#include <qdialog.h>
#include <QDialog>
#include <QSqlDatabase>
#include "Modelo/Usuario.h"
#include "Composicoes/PasswordFormHelper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class formLoginSenha; }
QT_END_NAMESPACE

class formLoginSenha : public QDialog {
Q_OBJECT

public:
    explicit formLoginSenha(const Usuario& usuario, QSqlDatabase db, QWidget *parent = nullptr);
    ~formLoginSenha() override;
private slots:
    void on_buttonEntrar_clicked();

private:
    Ui::formLoginSenha *ui;
    QSqlDatabase m_db;
    Usuario m_usuario;
    PasswordFormHelper *m_passwordHelper;
};


#endif //FORMLOGINSENHA_H
