#include "AppController.h"
#include "DataAccess/UsuarioDAO.h"
#include "Gerenciamento/SessionManager.h"
#include "Designer/formInicio.h"
#include "Designer/FormsLogin/formBoasVindas.h"
#include "Designer/FormsDashboard/formMainDashboard.h"
#include <QApplication>
#include <QDebug>

AppController::AppController(QObject *parent) : QObject(parent)
{
    m_formInicio = nullptr;
    m_dashboard = nullptr;
    m_idUsuarioRequisitado = -1;

    // Criamos o DAO uma única vez e o mantemos vivo
    m_usuarioDAO = new UsuarioDAO(this);

    // Conectamos os sinais do DAO aos nossos slots UMA ÚNICA VEZ
    connect(m_usuarioDAO, &UsuarioDAO::usuarioInicialRecebido, this, &AppController::onUsuarioInicialRecebido);
    connect(m_usuarioDAO, &UsuarioDAO::erroDeRede, this, [=](const QString& erro){
        // Lógica para tratar erros de rede, talvez com uma QMessageBox
        qDebug() << "ERRO DE REDE GLOBAL:" << erro;
    });

    // Conectamos o sinal global de reinício do SessionManager
    connect(&SessionManager::instance(), &SessionManager::precisaReiniciarParaLogin, this, &AppController::onSessaoReiniciada);
}

AppController::~AppController()
{
    // O Qt cuidará de deletar os filhos, mas é uma boa prática
}

void AppController::iniciarAplicacao()
{
    qDebug() << "Controlador: Iniciando aplicação, buscando usuário preferencial...";
    // Linha modificada: Em vez de pegar o ID da sessão ATUAL,
    // pega o ID que foi SALVO como preferencial.
    int idSalvo = SessionManager::instance().obterIdUsuarioPreferencial();

    m_usuarioDAO->obterUsuarioPreferencial(idSalvo);
}

void AppController::onUsuarioInicialRecebido(const std::optional<Usuario>& usuario)
{
    qDebug() << "Controlador: Resposta da API recebida.";

    // --- LÓGICA DE AUTOCORREÇÃO ---
    // SE: não recebemos um usuário (optional vazio) E estávamos esperando um usuário específico (ID era diferente de -1)
    if (!usuario.has_value() && m_idUsuarioRequisitado != -1) {
        qDebug() << "Controlador: O usuário preferencial com ID" << m_idUsuarioRequisitado << "é inválido. Limpando preferência e reiniciando.";

        // Limpa a configuração inválida para não tentar de novo no futuro.
        SessionManager::instance().salvarUsuarioPreferencial(-1);

        // Reinicia o fluxo da aplicação. Ele agora vai pedir o usuário "-1" (o mais recente).
        iniciarAplicacao();
        return; // Para a execução deste slot para esperar a nova resposta.
    }

    fecharJanelasAtuais();

    if (usuario) {
        // Se a API retornou um usuário, mostramos a tela de início
        mostrarTelaDeInicio(*usuario);
    } else {
        // Se não, mostramos a tela de boas-vindas
        mostrarTelaDeBoasVindas();
    }
}

void AppController::mostrarTelaDeInicio(const Usuario& usuarioInicial)
{
    qDebug() << "Controlador: Mostrando tela de início para" << usuarioInicial.nomeUsuario;
    m_formInicio = new formInicio(usuarioInicial, nullptr);
    // Conectamos o sinal de sucesso do login a um slot AQUI, no controlador
    connect(m_formInicio, &formInicio::loginBemSucedido, this, &AppController::onLoginSucesso);
    m_formInicio->show();
}

void AppController::mostrarTelaDeBoasVindas()
{
    qDebug() << "Controlador: Mostrando tela de boas-vindas.";
    formBoasVindas *boasVindas = new formBoasVindas(nullptr);
    // O formBoasVindas, ao ter um cadastro concluído, deve chamar o SessionManager
    // para reiniciar o app, assim como a troca de usuário.
    boasVindas->show();
}

void AppController::onLoginSucesso(const QString& token, const Usuario& usuario)
{
    qDebug() << "Controlador: Login bem-sucedido. Trocando para a Dashboard.";
    SessionManager::instance().criarSessao(token, usuario);

    fecharJanelasAtuais();

    m_dashboard = new formMainDashboard(nullptr);
    m_dashboard->showMaximized();
}

void AppController::onSessaoReiniciada()
{
    qDebug() << "Controlador: Logout ou troca de usuário. Reiniciando UI.";
    // O SessionManager já limpou a sessão e salvou a nova preferência.
    // Apenas chamamos o 'iniciar' de novo para recomeçar o ciclo.
    iniciarAplicacao();
}

void AppController::fecharJanelasAtuais()
{
    // Função auxiliar para garantir que as janelas antigas sejam fechadas e deletadas
    if (m_formInicio) {
        m_formInicio->close();
        m_formInicio->deleteLater();
        m_formInicio = nullptr;
    }
    if (m_dashboard) {
        m_dashboard->close();
        m_dashboard->deleteLater();
        m_dashboard = nullptr;
    }
    // Fecha também outras janelas de topo, como a de boas-vindas
    for (QWidget *widget : QApplication::topLevelWidgets()) {
        if (widget != m_formInicio && widget != m_dashboard) {
            widget->close();
            widget->deleteLater();
        }
    }
}
