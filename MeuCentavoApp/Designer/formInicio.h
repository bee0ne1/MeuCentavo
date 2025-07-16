#ifndef FORMINICIO_H
#define FORMINICIO_H

#include <QMainWindow>
#include "Modelo/Usuario.h"
#include <optional>

// Forward declarations
class formLoginSenha;
namespace Ui { class formInicio; }

class formInicio : public QMainWindow
{
    Q_OBJECT

public:
    // O construtor agora é muito mais simples, não precisa do banco de dados
    explicit formInicio(const Usuario& usuarioInicial,QWidget *parent = nullptr);
    ~formInicio();

private slots:
    // Slot para o clique no botão principal de login.
    void on_buttonAppAcess_clicked();

    // Slot que recebe o resultado do diálogo de senha.
    void onLoginFinalizado(const QString& token, const Usuario& usuario);

signals:
    // Sinal para avisar o AppController que o login foi um sucesso.
    // Ele carrega o token e os dados do usuário.
    void loginBemSucedido(const QString& token, const Usuario& usuario);

private:
    Ui::formInicio *ui;

    Usuario m_usuarioAtual;
};

#endif // FORMINICIO_H