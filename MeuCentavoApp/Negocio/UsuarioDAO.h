//
// Created by bruno on 29/06/25.
//

#ifndef USUARIODAO_H
#define USUARIODAO_H


#include <QObject>
#include <QSqlDatabase>
#include "Modelo/Usuario.h" // Incluindo a struct que acabamos de criar

class UsuarioDAO : public QObject {
    Q_OBJECT
public:
    explicit UsuarioDAO(QSqlDatabase db, QObject *parent = nullptr);

    // Método para inserir um novo usuário no banco
    bool adicionarUsuario(const Usuario& usuario);

    // Método para verificar se um usuário existe (útil para login)
    bool autenticarUsuario(const QString& nomeUsuario, const QString& senha);

    // Poderíamos adicionar outros:
    // Usuario obterUsuarioPorNome(const QString& nomeUsuario);
    // bool removerUsuario(int id);

private:
    QSqlDatabase m_db; // Instância da conexão com o banco
};



#endif //USUARIODAO_H
