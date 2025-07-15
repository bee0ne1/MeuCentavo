#include "SessionManager.h"

SessionManager& SessionManager::instance()
{
    // A instância é criada na primeira vez que é chamada e reutilizada sempre
    static SessionManager singleton;
    return singleton;
}

SessionManager::SessionManager() : m_token(""), m_usuarioAtual(std::nullopt) {}

void SessionManager::criarSessao(const QString& token, const Usuario& usuario)
{
    m_token = token;
    m_usuarioAtual = usuario;
}

void SessionManager::encerrarSessao()
{
    m_token.clear();
    m_usuarioAtual.reset();
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