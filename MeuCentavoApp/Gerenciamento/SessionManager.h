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

    bool estaLogado() const;
    QString getToken() const;
    Usuario getUsuario() const;
    int getUsuarioId() const;

signals:
    void precisaReiniciarParaLogin();



private:
    // Construtor privado para que ninguém de fora possa criar uma instância
    SessionManager();

    QString m_token;
    std::optional<Usuario> m_usuarioAtual;
};

#endif // SESSIONMANAGER_H