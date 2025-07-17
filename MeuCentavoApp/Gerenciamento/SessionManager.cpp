#include "SessionManager.h"
#include <QSettings>
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