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

std::optional<Usuario> UsuarioDAO::autenticarEObterUsuario(const QString& nomeUsuario, const QString& senha)
{
    QSqlQuery query(m_db);
    // Selecionamos os dados que queremos do usuário
    query.prepare("SELECT user_id, user_usuario FROM usuario WHERE user_usuario = :nome AND user_password = :senha");
    query.bindValue(":nome", nomeUsuario);
    query.bindValue(":senha", senha);

    if (query.exec() && query.next()) {
        // Se encontrou, preenchemos a struct com os dados do banco
        Usuario usuarioLogado;
        usuarioLogado.id = query.value("user_id").toInt();
        usuarioLogado.nomeUsuario = query.value("user_usuario").toString();
        // ... pode pegar mais dados se quiser ...

        // Retorna o objeto de usuário preenchido
        return usuarioLogado;
    }

    // Se a query falhou ou não encontrou nenhum usuário, retorna um "opcional vazio"
    return std::nullopt;
}

QVector<Usuario> UsuarioDAO::obterTodosUsuarios()
{
    // 1. Cria o vetor que será retornado
    QVector<Usuario> listaDeUsuarios;

    QSqlQuery query(m_db);
    QString sql = "SELECT user_id, user_usuario FROM usuario ORDER BY user_usuario ASC";

    // 2. Prepara e executa a query
    if (!query.prepare(sql)) {
        qDebug() << "Erro ao preparar a query para obter todos os usuários:" << query.lastError().text();
        return listaDeUsuarios; // Retorna a lista vazia em caso de erro
    }

    if (!query.exec()) {
        qDebug() << "Erro ao executar a query para obter todos os usuários:" << query.lastError().text();
        return listaDeUsuarios; // Retorna a lista vazia em caso de erro
    }

    // 3. Itera sobre os resultados
    while (query.next()) {
        // Para cada linha retornada pelo banco...
        Usuario usuario; // Cria uma struct temporária

        // Preenche a struct com os dados da linha atual
        usuario.id = query.value("user_id").toInt();
        usuario.nomeUsuario = query.value("user_usuario").toString();

        // Adiciona a struct preenchida ao nosso vetor
        listaDeUsuarios.append(usuario);
    }

    // 4. Retorna a lista completa
    return listaDeUsuarios;
}

std::optional<Usuario> UsuarioDAO::obterUltimoUsuario()
{
    QSqlQuery query(m_db);
    // ORDER BY user_id DESC pega o maior ID (o mais recente)
    // LIMIT 1 garante que pegaremos apenas uma linha
    QString sql = "SELECT user_id, user_usuario FROM usuario ORDER BY user_id DESC LIMIT 1";

    if (query.exec(sql) && query.next()) {
        Usuario usuario;
        usuario.id = query.value("user_id").toInt();
        usuario.nomeUsuario = query.value("user_usuario").toString();
        return usuario;
    }

    qDebug() << "Nenhum usuário encontrado no banco de dados.";
    return std::nullopt;
}

std::optional<Usuario> UsuarioDAO::obterUsuarioPorId(int id)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT user_id, user_usuario FROM usuario WHERE user_id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        Usuario usuario;
        usuario.id = query.value("user_id").toInt();
        usuario.nomeUsuario = query.value("user_usuario").toString();
        return usuario;
    }
    return std::nullopt; // Retorna vazio se não encontrar
}

bool UsuarioDAO::removerUsuario(int id)
{
    QSqlQuery query(m_db);
    // Usamos um placeholder :id para segurança (evitar SQL Injection)
    query.prepare("DELETE FROM usuario WHERE user_id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Usuário com ID" << id << "removido com sucesso.";
        return true;
    } else {
        qDebug() << "Erro ao remover usuário:" << query.lastError().text();
        return false;
    }
}

bool UsuarioDAO::existeUsuario(const QString& nomeUsuario)
{
    QSqlQuery query(m_db);
    // Usamos COUNT(*) que é otimizado para contar linhas.
    // A query retorna uma única linha com a contagem de usuários com aquele nome.
    query.prepare("SELECT COUNT(*) FROM usuario WHERE user_usuario = :nome");
    query.bindValue(":nome", nomeUsuario);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return (count > 0); // Se a contagem for > 0, o usuário existe.
    }

    qDebug() << "Erro ao verificar a existência do usuário:" << query.lastError().text();
    return false;
}

bool UsuarioDAO::existemUsuarios()
{
    QSqlQuery query(m_db);
    // COUNT(*) é a forma mais rápida de contar o número de linhas.
    query.prepare("SELECT COUNT(*) FROM usuario");

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return (count > 0); // Retorna true se houver 1 ou mais usuários.
    }

    qDebug() << "Erro ao verificar se existem usuários:" << query.lastError().text();
    return false; // Em caso de erro, assume que não existem.
}