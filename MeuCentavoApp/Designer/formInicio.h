#ifndef FORMINICIO_H
#define FORMINICIO_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "Modelo/Usuario.h"
#include <optional>

class formUsuario;
class formLoginSenha;

QT_BEGIN_NAMESPACE
namespace Ui {
    class formInicio;
}
QT_END_NAMESPACE

class formInicio : public QMainWindow {
    Q_OBJECT

public:

    explicit formInicio(QSqlDatabase db, QWidget *parent = nullptr);

    ~formInicio();


public slots:
    void carregarUsuarioInicial();
    void atualizarUsuarioNoBotao(const Usuario& usuario);

private slots:
    void abrirTelaUsuario();
    void abrirTelaLogin();

private:
    Ui::formInicio *ui;
    formUsuario *usuarioWindow = nullptr;
    QSqlDatabase m_db; // Variável membro para GUARDAR a conexão recebida.
    std::optional<Usuario> m_usuarioAtual; // Usamos std::optional para representar um usuário que pode ou não estar carregado.

};

#endif // FORMINICIO_H
