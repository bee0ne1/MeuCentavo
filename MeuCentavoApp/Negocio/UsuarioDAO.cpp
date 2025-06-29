//
// Created by bruno on 29/06/25.
//

#include "UsuarioDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

UsuarioDAO::UsuarioDAO(QSqlDatabase db, QObject *parent)
    : QObject(parent), m_db(db) {}

// --- MÉTODO PARA INSERIR UM NOVO USUÁRIO ---
bool UsuarioDAO::adicionarUsuario(const Usuario& usuario) {
    QSqlQuery query(m_db);

    // Prepara o comando SQL para a tabela 'usuario' com os campos corretos
    QString sql = "INSERT INTO usuario (user_usuario, user_password) "
                  "VALUES (:nome_usuario, :senha)";

    if (!query.prepare(sql)) {
        qDebug() << "Erro ao preparar a query de inserção de usuário:" << query.lastError().text();
        return false;
    }

    // Associa os valores da nossa struct aos placeholders da query
    query.bindValue(":nome_usuario", usuario.nomeUsuario);
    query.bindValue(":senha", usuario.senha); // Idealmente, a senha deveria ser criptografada antes!

    if (!query.exec()) {
        qDebug() << "Erro ao executar a query de inserção de usuário:" << query.lastError().text();
        return false;
    }

    qDebug() << "Usuário" << usuario.nomeUsuario << "inserido com sucesso!";
    return true;
}


// --- MÉTODO BÔNUS PARA AUTENTICAÇÃO ---
bool UsuarioDAO::autenticarUsuario(const QString& nomeUsuario, const QString& senha) {
    QSqlQuery query(m_db);

    QString sql = "SELECT COUNT(*) FROM usuario WHERE user_usuario = :nome_usuario AND user_password = :senha";

    if (!query.prepare(sql)) {
        qDebug() << "Erro ao preparar a query de autenticação:" << query.lastError().text();
        return false;
    }

    query.bindValue(":nome_usuario", nomeUsuario);
    query.bindValue(":senha", senha);

    if (!query.exec()) {
        qDebug() << "Erro ao executar a query de autenticação:" << query.lastError().text();
        return false;
    }

    // Se a query retornou uma linha, vamos pegar o resultado
    if (query.next()) {
        int count = query.value(0).toInt();
        return (count > 0); // Retorna true se encontrou 1 (ou mais) usuário, false caso contrário
    }

    return false; // Se não conseguiu nem ler o resultado
}
