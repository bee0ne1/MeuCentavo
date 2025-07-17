#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include "Modelo/Usuario.h" // Inclui a struct para o std::optional
#include <optional>

// Forward declarations para evitar includes circulares
class formInicio;
class formMainDashboard;
class UsuarioDAO;

class AppController : public QObject
{
    Q_OBJECT

public:
    explicit AppController(QObject *parent = nullptr);
    ~AppController();

    // O método que a main() vai chamar para iniciar todo o fluxo
    void iniciarAplicacao();

private slots:
    // Slot que reage à resposta da API ao buscar o usuário inicial
    void onUsuarioInicialRecebido(const std::optional<Usuario>& usuario);

    // Slot que reage ao sinal de login bem-sucedido vindo da formInicio
    void onLoginSucesso(const QString& token, const Usuario& usuario);

    // Slot que reage ao sinal do SessionManager para reiniciar a UI (logout/troca de usuário)
    void onSessaoReiniciada();

private:
    // Funções privadas para organizar a criação das janelas
    void mostrarTelaDeInicio(const Usuario& usuario);
    void mostrarTelaDeBoasVindas();
    void fecharJanelasAtuais();

    // O controlador agora "possui" as janelas principais e o DAO
    formInicio* m_formInicio;
    formMainDashboard* m_dashboard;
    UsuarioDAO* m_usuarioDAO;
    int m_idUsuarioRequisitado;
};

#endif // APPCONTROLLER_H
