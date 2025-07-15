#ifndef FORMINICIO_H
#define FORMINICIO_H

#include <QMainWindow>
#include "Modelo/Usuario.h"
#include <optional>

// Forward declarations
class formUsuario;
class formLoginSenha;
class UsuarioDAO;
namespace Ui { class formInicio; }

class formInicio : public QMainWindow
{
    Q_OBJECT

public:
    // O construtor agora é muito mais simples, não precisa do banco de dados
    explicit formInicio(QWidget *parent = nullptr);
    ~formInicio();

private slots:
    // Slots para os botões da UI
    void abrirTelaSelecaoUsuario();
    void tentarLogin();

    // Slots para receber as respostas do DAO
    void onUsuarioInicialRecebido(const std::optional<Usuario>& usuario);
    void onUsuarioSelecionado(const Usuario& usuario);
    void onLoginSucesso(const QString& token, const Usuario& usuario);
    void onLoginFalhou(const QString& motivo);

private:
    Ui::formInicio *ui;

    // Ponteiros para as outras janelas
    formUsuario *m_formUsuario;

    // Variável para guardar o usuário que está atualmente em exibição no botão
    std::optional<Usuario> m_usuarioAtual;
};

#endif // FORMINICIO_H