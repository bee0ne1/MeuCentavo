#ifndef USUARIODAO_H
#define USUARIODAO_H

#include <QObject>
#include <QVector>
#include "Modelo/Usuario.h"
#include "Modelo/Perfil.h"
#include <optional>

// Forward declarations para as classes de rede
class QNetworkAccessManager;
class QNetworkReply;

class UsuarioDAO : public QObject
{
    Q_OBJECT
public:
    // O construtor agora é mais simples, não precisa mais do 'db'
    explicit UsuarioDAO(QObject *parent = nullptr);

    // --- MÉTODOS PÚBLICOS ---
    // Eles iniciam a requisição de rede, mas não retornam o resultado diretamente.
    void registrarUsuario(const QString& username, const QString& password);
    void logarUsuario(const QString& username, const QString& password);
    void obterTodosUsuarios(const QString& token); // Precisa do token para autorização
    void obterUsuarioPreferencial(int id);
    void removerUsuario(int usuarioId, const QString& token);
    void obterPerfis(const QString& token);
    void adicionarPerfil(const Perfil& perfil, const QString& token);
    void selecionarPerfil(int idPerfil, const QString& token);
    void excluirPerfil(int idPerfil, const QString& token);

signals:
        // --- SINAIS PARA COMUNICAR O RESULTADO ---
        // A interface vai se conectar a estes sinais para saber quando uma operação terminou.
    void registroSucesso(const Usuario& novoUsuario);
    void loginSucesso(const QString& token, const Usuario& usuario);
    void todosUsuariosRecebidos(const QVector<Usuario>& usuarios);
    void erroDeAutenticacao(const QString& mensagem);
    void erroDeRede(const QString& mensagem);
    void usuarioInicialRecebido(const std::optional<Usuario>& usuario);
    void registroFalhou(const QString& motivo);
    void remocaoSucesso();
    void perfisRecebidos(const QVector<Perfil>& perfis);
    void perfilAdicionadoComSucesso();
    void novoTokenRecebido(const QString& novoToken, const Usuario& usuario);
    void perfilExcluidoComSucesso();

private slots:
    // Slots privados que serão chamados quando o servidor responder.
    void onRegistroReply(QNetworkReply *reply);
    void onLoginReply(QNetworkReply *reply);
    void onObterTodosReply(QNetworkReply *reply);
    void onUsuarioPreferencialReply(QNetworkReply *reply);
    void onRemoverUsuarioReply(QNetworkReply *reply);
    void onObterPerfisReply(QNetworkReply *reply);
    void onAdicionarPerfilReply(QNetworkReply *reply);
    void onSelecionarPerfilReply(QNetworkReply *reply);
    void onExcluirPerfilReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
    QString m_baseUrl = "http://localhost:3000/api/usuarios"; // URL base da nossa API de usuários
    QString m_perfisUrl = "http://localhost:3000/api/perfis";
};

#endif // USUARIODAO_H