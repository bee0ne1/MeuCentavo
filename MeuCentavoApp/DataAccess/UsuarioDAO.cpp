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

    // Conecta a resposta ao nosso slot privado
    connect(m_manager, &QNetworkAccessManager::finished, this, &UsuarioDAO::onRegistroReply);

    m_manager->post(request, QJsonDocument(json).toJson());
}

void UsuarioDAO::onRegistroReply(QNetworkReply *reply)
{
    qDebug() << "DAO: Resposta do registro recebida!";

    // Verifica se houve um erro de rede (ex: servidor offline)
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "DAO: Erro de rede:" << reply->errorString();
        emit registroFalhou("Erro de rede: " + reply->errorString());
        reply->deleteLater(); // Limpa a memória
        return;
    }

    // Lê o código de status HTTP da resposta (ex: 201, 409, 500)
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    // Lê o corpo da resposta
    QByteArray responseData = reply->readAll();

    qDebug() << "DAO: Status Code:" << statusCode;
    qDebug() << "DAO: Corpo da Resposta:" << responseData;

    // Se o status code for 201 (Created), o registro foi um sucesso!
    if (statusCode == 201) {
        emit registroSucesso();
    } else {
        // Se for outro status, consideramos um erro e pegamos a mensagem do backend
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QString motivo = jsonDoc.object()["message"].toString();
        if (motivo.isEmpty()) {
            motivo = "Ocorreu um erro desconhecido no servidor.";
        }
        emit registroFalhou(motivo);
    }

    // Essencial: marca o objeto de resposta para ser deletado, evitando vazamento de memória.
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

    connect(m_manager, &QNetworkAccessManager::finished, this, &UsuarioDAO::onLoginReply);
    m_manager->post(request, QJsonDocument(json).toJson());
}

void UsuarioDAO::onLoginReply(QNetworkReply *reply)
{
    disconnect(m_manager, &QNetworkAccessManager::finished, this, &UsuarioDAO::onLoginReply);

    if (reply->error() == QNetworkReply::NoError) {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();

        if (statusCode == 200) { // 200 OK
            QString token = jsonObj["token"].toString();
            // Supondo que o backend também retorna os dados do usuário no login
            Usuario usuario;
            usuario.id = jsonObj["user"].toObject()["userId"].toInt();
            usuario.nomeUsuario = jsonObj["user"].toObject()["username"].toString();
            emit loginSucesso(token, usuario);
        } else { // ex: 401 Unauthorized
            emit erroDeAutenticacao(jsonObj["message"].toString());
        }
    } else {
        emit erroDeRede(reply->errorString());
    }
    reply->deleteLater();
}


// --- OBTER TODOS OS USUÁRIOS (Exemplo de requisição autenticada) ---
void UsuarioDAO::obterTodosUsuarios(const QString& token)
{
    // Esta rota precisaria ser criada no seu backend
    QNetworkRequest request(QUrl(m_baseUrl + "/"));
    // Adiciona o token JWT no cabeçalho para provar que estamos logados
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    connect(m_manager, &QNetworkAccessManager::finished, this, &UsuarioDAO::onObterTodosReply);
    m_manager->get(request);
}

void UsuarioDAO::onObterTodosReply(QNetworkReply *reply)
{
    // ... Lógica para processar a resposta, similar ao onObterTodosLancamentosFinished ...
    // ... que emitiria o sinal todosUsuariosRecebidos(lista) ...
    reply->deleteLater();
}

void UsuarioDAO::obterUsuarioInicial()
{
    // Esta requisição vai para um novo endpoint que você criará no backend.
    // Ex: GET /api/usuarios/inicial
    // Este endpoint pode ler o QSettings (enviado como parâmetro) ou pegar o último usuário do banco.
    // Por simplicidade aqui, vamos assumir que ele retorna o último usuário.
    QNetworkRequest request(QUrl(m_baseUrl + "/inicial"));

    // Conecta a resposta ao nosso novo slot
    connect(m_manager, &QNetworkAccessManager::finished, this, &UsuarioDAO::onUsuarioInicialReply);

    // Envia a requisição GET
    m_manager->get(request);
}

void UsuarioDAO::onUsuarioInicialReply(QNetworkReply *reply)
{
    disconnect(m_manager, &QNetworkAccessManager::finished, this, &UsuarioDAO::onUsuarioInicialReply);

    std::optional<Usuario> usuarioEncontrado; // Começa como vazio

    if (reply->error() == QNetworkReply::NoError && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();

        // Se o backend retornou um objeto de usuário...
        if (!jsonObj.isEmpty()) {
            Usuario u;
            u.id = jsonObj["user_id"].toInt();
            u.nomeUsuario = jsonObj["user_usuario"].toString();
            usuarioEncontrado = u;
            qDebug() << "DAO: Usuário inicial recebido da API:" << u.nomeUsuario;
        } else {
            // Se o backend retornou um corpo vazio (ex: banco de dados vazio)
            qDebug() << "DAO: API não retornou um usuário inicial.";
        }
    } else {
        qDebug() << "DAO: Erro ao buscar usuário inicial:" << reply->errorString();
        // Não emitimos um erro de rede aqui, pois pode ser simplesmente que o banco está vazio (um 404, por exemplo)
    }

    // Emite o sinal com o resultado, seja um usuário ou um optional vazio.
    emit usuarioInicialRecebido(usuarioEncontrado);

    reply->deleteLater();
}

void UsuarioDAO::removerUsuario(int usuarioId, const QString& token)
{
    // Rota: DELETE /api/usuarios/:id
    QNetworkRequest request(QUrl(m_baseUrl + "/" + QString::number(usuarioId)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    connect(m_manager, &QNetworkAccessManager::finished, this, &UsuarioDAO::onRemoverUsuarioReply);
    m_manager->deleteResource(request);
}

void UsuarioDAO::onRemoverUsuarioReply(QNetworkReply *reply)
{
    // Desconecta o sinal para esta requisição específica.
    disconnect(m_manager, &QNetworkAccessManager::finished, this, &UsuarioDAO::onRemoverUsuarioReply);

    qDebug() << "DAO: Resposta da remoção recebida.";

    if (reply->error() != QNetworkReply::NoError) {
        // Erro de rede (ex: servidor offline, sem conexão)
        emit erroDeRede("Erro de rede ao tentar remover usuário: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "DAO: Status Code da remoção:" << statusCode;

    // HTTP Status 200 OK ou 204 No Content são respostas comuns para um DELETE bem-sucedido.
    if (statusCode == 200 || statusCode == 204) {
        // Deu certo! Emite o sinal de sucesso.
        emit remocaoSucesso();
    } else {
        // Se for outro status, como 403 (Proibido) ou 404 (Não encontrado), tratamos como erro.
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QString motivo = jsonDoc.object()["message"].toString();
        emit erroDeRede("Não foi possível remover o usuário: " + motivo);
    }

    // Essencial para limpar a memória do objeto de resposta.
    reply->deleteLater();
}