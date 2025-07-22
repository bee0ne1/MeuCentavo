#include "UsuarioDAO.h"

// Includes necessários para rede e JSON
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

UsuarioDAO::UsuarioDAO(QObject *parent)
    : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

// --- REGISTRO ---
void UsuarioDAO::registrarUsuario(const QString& username, const QString& password)
{
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;

    QNetworkRequest request(QUrl(m_baseUrl + "/registrar"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onRegistroReply(reply);
    });
}

void UsuarioDAO::onRegistroReply(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray responseData = reply->readAll();

    if (statusCode == 201) {
        QJsonObject jsonObj = QJsonDocument::fromJson(responseData).object();
        QJsonObject userObj = jsonObj["user"].toObject();
        Usuario novoUsuario;
        novoUsuario.id = userObj["user_id"].toInt();
        novoUsuario.nomeUsuario = userObj["user_usuario"].toString();
        emit registroSucesso(novoUsuario);
    } else {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QString motivo = jsonDoc.object()["message"].toString();
        if (motivo.isEmpty()) {
            motivo = "Erro no servidor: " + reply->errorString();
        }
        emit registroFalhou(motivo);
    }
    reply->deleteLater();
}

// --- LOGIN ---
void UsuarioDAO::logarUsuario(const QString& username, const QString& password)
{
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;

    QNetworkRequest request(QUrl(m_baseUrl + "/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // PADRÃO CORRIGIDO:
    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onLoginReply(reply);
    });
}

void UsuarioDAO::onLoginReply(QNetworkReply *reply)
{
    // Lemos sempre o status e o corpo da resposta primeiro
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray responseData = reply->readAll();

    // Verificamos se o status code é de SUCESSO
    if (statusCode == 200) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();

        QString token = jsonObj["token"].toString();

        Usuario usuario;
        // O seu backend retorna um objeto 'user' dentro do JSON no login
        QJsonObject userObj = jsonObj["user"].toObject();
        usuario.id = userObj["user_id"].toInt();
        usuario.nomeUsuario = userObj["user_usuario"].toString();

        emit loginSucesso(token, usuario);

    } else {
        // Se o status code for qualquer outra coisa (401, 404, 500), tratamos como erro
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();

        // Tentamos extrair a mensagem específica do nosso backend
        QString motivo = jsonObj["message"].toString();

        // Se, por alguma razão, não houver mensagem, usamos o erro padrão do Qt
        if (motivo.isEmpty()) {
            motivo = reply->errorString();
        }

        // Emitimos o sinal específico de falha de autenticação
        emit erroDeAutenticacao(motivo);
    }

    reply->deleteLater();
}


// --- OBTER TODOS OS USUÁRIOS (Exemplo de requisição autenticada) ---
void UsuarioDAO::obterTodosUsuarios(const QString& token)
{
    QNetworkRequest request(QUrl(m_baseUrl + "/"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    // PADRÃO CORRIGIDO:
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onObterTodosReply(reply);
    });
}

void UsuarioDAO::onObterTodosReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        QVector<Usuario> listaDeUsuarios;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            Usuario u;
            u.id = obj["user_id"].toInt();
            u.nomeUsuario = obj["user_usuario"].toString();
            listaDeUsuarios.append(u);
        }
        emit todosUsuariosRecebidos(listaDeUsuarios);
    } else {
        emit erroDeRede("Não foi possível carregar a lista de usuários: " + reply->errorString());
    }
    reply->deleteLater();
}

void UsuarioDAO::obterUsuarioPreferencial(int id)
{
    QUrl url;

    if (id == -1) {
        // Se o ID for -1, não há preferência salva. Buscamos o último usuário cadastrado.
        qDebug() << "DAO: Nenhum ID salvo. Buscando o último usuário na rota /inicial.";
        url = QUrl(m_baseUrl + "/inicial");
    } else {
        // Se temos um ID, buscamos por ele especificamente.
        qDebug() << "DAO: Buscando usuário com ID específico:" << id;
        url = QUrl(m_baseUrl + "/" + QString::number(id));
    }

    QNetworkRequest request(url);
    // Esta requisição não precisa de token, pois é para a tela de início.

    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onUsuarioPreferencialReply(reply);
    });
}

void UsuarioDAO::onUsuarioPreferencialReply(QNetworkReply *reply)
{
    std::optional<Usuario> usuarioEncontrado;
    // Apenas verifica se a requisição deu certo (status 200) e popula o usuário.
    if (reply->error() == QNetworkReply::NoError && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();
        if (!jsonObj.isEmpty()) {
            Usuario u;
            u.id = jsonObj["user_id"].toInt();
            u.nomeUsuario = jsonObj["user_usuario"].toString();
            usuarioEncontrado = u;
            qDebug() << "DAO: Usuário inicial recebido da API:" << u.nomeUsuario;
        }
    } else if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "DAO: Erro ao buscar usuário inicial:" << reply->errorString();
    }
    // Se deu 404, ele simplesmente não entra no if e emite o sinal com o optional vazio.

    emit usuarioInicialRecebido(usuarioEncontrado);
    reply->deleteLater();
}

void UsuarioDAO::removerUsuario(int usuarioId, const QString& token)
{
    // Rota: DELETE /api/usuarios/:id
    QNetworkRequest request(QUrl(m_baseUrl + "/" + QString::number(usuarioId)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onRemoverUsuarioReply(reply);
    });
}

void UsuarioDAO::onRemoverUsuarioReply(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() == QNetworkReply::NoError && (statusCode == 200 || statusCode == 204)) {
        emit remocaoSucesso();
    } else {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QString motivo = jsonDoc.object()["message"].toString();
        if(motivo.isEmpty()) motivo = "Não foi possível remover o usuário: " + reply->errorString();
        emit erroDeRede(motivo);
    }
    reply->deleteLater();
}