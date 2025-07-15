#ifndef FORMLOGINSENHA_H
#define FORMLOGINSENHA_H

#include <QDialog>
#include "Modelo/Usuario.h"
#include "Composicoes/PasswordFormHelper.h"

// Forward declaration
namespace Ui { class formLoginSenha; }
class UsuarioDAO;

class formLoginSenha : public QDialog
{
    Q_OBJECT

public:
    // O construtor agora só precisa do usuário para quem estamos pedindo a senha.
    explicit formLoginSenha(const Usuario& usuario, QWidget *parent = nullptr);
    ~formLoginSenha();

    signals:
        // Sinal que será emitido quando o login for bem-sucedido.
        // Ele carrega o token e os dados do usuário para a janela principal.
        void loginSucesso(const QString& token, const Usuario& usuario);

private slots:
    // Slot para o botão "Entrar"
    void tentarLogin();
    // Slots para reagir às respostas do DAO
    void onLoginSucesso(const QString& token, const Usuario& usuario);
    void onLoginFalhou(const QString& motivo);

private:
    Ui::formLoginSenha *ui;
    Usuario m_usuario; // Guarda o usuário que está tentando logar
    PasswordFormHelper *m_passwordHelper;
};

#endif // FORMLOGINSENHA_H