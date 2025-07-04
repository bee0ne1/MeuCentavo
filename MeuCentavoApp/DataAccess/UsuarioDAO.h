//
// Created by bruno on 29/06/25.
//

#ifndef USUARIODAO_H
#define USUARIODAO_H


#include <QObject>
#include <QSqlDatabase>
#include "Modelo/Usuario.h" // Incluindo a struct que acabamos de criar
#include <optional> // Essencial para o retorno opcional


class UsuarioDAO : public QObject {
    Q_OBJECT
public:
    explicit UsuarioDAO(QSqlDatabase db, QObject *parent = nullptr);

    // Método para inserir um novo usuário no banco
    bool adicionarUsuario(const Usuario& usuario);

    // Método para verificar se um usuário existe (útil para login)
    bool autenticarUsuario(const QString& nomeUsuario, const QString& senha);

    // Esta função retorna o usuário se o login for válido, ou nada se for inválido.
    std::optional<Usuario> autenticarEObterUsuario(const QString& nomeUsuario, const QString& senha);
    QVector<Usuario> obterTodosUsuarios();
    std::optional<Usuario> obterUltimoUsuario();
    std::optional<Usuario> obterUsuarioPorId(int id);
    bool removerUsuario(int id);
    bool existeUsuario(const QString& nomeUsuario);
    bool existemUsuarios();

    // Poderíamos adicionar outros:
    // Usuario obterUsuarioPorNome(const QString& nomeUsuario);


private:
    QSqlDatabase m_db; // Instância da conexão com o banco
};



#endif //USUARIODAO_H
