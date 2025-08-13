#include "SessionManager.h"
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>

SessionManager& SessionManager::instance()
{
    // A instância é criada na primeira vez que é chamada e reutilizada sempre
    static SessionManager singleton;
    return singleton;
}

SessionManager::SessionManager() : m_token(""), m_usuarioAtual(std::nullopt), m_perfilIdAtivo(-1),m_tipoPerfilAtivo("") {}

void SessionManager::criarSessao(const QString& token, const Usuario& usuario)
{
    m_token = token;
    m_usuarioAtual = usuario;
    // --- LÓGICA PARA DECODIFICAR O TOKEN E EXTRAIR O PERFILID ---
    // Um token JWT é dividido em 3 partes por pontos: header.payload.signature
    QStringList parts = token.split('.');
    if (parts.size() >= 2) {
        // A segunda parte (payload) contém os dados
        QByteArray payloadData = QByteArray::fromBase64(parts[1].toUtf8(), QByteArray::Base64UrlEncoding);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(payloadData);
        if (!jsonDoc.isNull()) {
            QJsonObject payloadObj = jsonDoc.object();
            // Lemos a chave "perfilId" que o nosso backend Node.js adicionou
            m_perfilIdAtivo = payloadObj["perfilId"].toInt(-1); // Usa -1 como padrão se não encontrar
            m_tipoPerfilAtivo = payloadObj["tipoPerfil"].toString(); // Lê o tipo do perfil
            qDebug() << "SessionManager: Perfil ID ativo extraído do token:" << m_perfilIdAtivo;
        }
    }
}

void SessionManager::encerrarSessao()
{
    m_token.clear();
    m_usuarioAtual.reset();

    // Emite o sinal para que o AppController possa reagir
    emit precisaReiniciarParaLogin();
}

// Nova função para orquestrar a troca de usuário
void SessionManager::trocarUsuario(const Usuario& novoUsuario)
{
    // Salva o novo usuário como preferencial
    salvarUsuarioPreferencial(novoUsuario.id);
    // Emite o sinal para o AppController reiniciar a UI
    emit precisaReiniciarParaLogin();
}


bool SessionManager::estaLogado() const
{
    return m_usuarioAtual.has_value();
}

QString SessionManager::getToken() const
{
    return m_token;
}

Usuario SessionManager::getUsuario() const
{
    // Retorna o usuário ou um usuário vazio se não estiver logado
    return m_usuarioAtual.value_or(Usuario());
}

int SessionManager::getUsuarioId() const
{
    if (m_usuarioAtual) {
        return m_usuarioAtual->id;
    }
    return -1; // Retorna -1 se não houver usuário logado
}

void SessionManager::salvarUsuarioPreferencial(int usuarioId)
{
    QSettings settings;
    settings.setValue("preferentialUserId", usuarioId);
}

int SessionManager::obterIdUsuarioPreferencial() const
{
    QSettings settings;
    // Retorna o ID salvo, ou -1 se não houver nenhum.
    return settings.value("preferentialUserId", -1).toInt();
}

int SessionManager::getPerfilId() const
{
    return m_perfilIdAtivo;
}

// Esta função atualiza o token e o perfil ativo na sessão atual
void SessionManager::salvarNovoToken(const QString& novoToken)
{
    m_token = novoToken;

    // Decodifica o novo token para atualizar o ID do perfil ativo
    QStringList parts = novoToken.split('.');
    if (parts.size() >= 2) {
        QByteArray payloadData = QByteArray::fromBase64(parts[1].toUtf8(), QByteArray::Base64UrlEncoding);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(payloadData);
        if (!jsonDoc.isNull()) {
            QJsonObject payloadObj = jsonDoc.object();
            m_perfilIdAtivo = payloadObj["perfilId"].toInt(-1);
            m_tipoPerfilAtivo = payloadObj["tipoPerfil"].toString(); // Lê o tipo do perfil
            qDebug() << "SessionManager: Sessão atualizada com novo token. Novo Perfil ID:" << m_perfilIdAtivo;
        }
    }
    emit sessaoAtualizada();
}

QString SessionManager::getTipoPerfil() const
{
    return m_tipoPerfilAtivo;
}

// Esta função simplesmente emite o sinal para o AppController reiniciar a interface
void SessionManager::reiniciarSessao()
{
    // O AppController está conectado a este sinal e irá recarregar a UI
    emit precisaReiniciarParaLogin();
}