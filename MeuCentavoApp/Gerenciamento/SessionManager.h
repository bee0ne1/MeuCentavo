#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "Modelo/Usuario.h"
#include <QString>
#include <optional>
#include <QObject>

class SessionManager: public QObject
{ Q_OBJECT

public:
    // Método estático para acessar a única instância da classe
    static SessionManager& instance();

    // Deleta os construtores de cópia para garantir que seja um singleton
    SessionManager(const SessionManager&) = delete;
    void operator=(const SessionManager&) = delete;

    // Métodos para gerenciar a sessão
    void criarSessao(const QString& token, const Usuario& usuario);
    void encerrarSessao();
    void trocarUsuario(const Usuario& novoUsuario);
    void salvarUsuarioPreferencial(int usuarioId);

    bool estaLogado() const;
    QString getToken() const;
    Usuario getUsuario() const;
    int getUsuarioId() const;
    int getPerfilId() const;
    QString getTipoPerfil() const;
    int obterIdUsuarioPreferencial() const;
    void salvarNovoToken(const QString& novoToken);
    void reiniciarSessao();

signals:
    void precisaReiniciarParaLogin();
    void sessaoAtualizada();


private:
    // Construtor privado para que ninguém de fora possa criar uma instância
    SessionManager();

    QString m_token;
    std::optional<Usuario> m_usuarioAtual;
    int m_perfilIdAtivo;
    QString m_tipoPerfilAtivo;
};

#endif // SESSIONMANAGER_H