#include "formInicio.h"
#include "ui_formInicio.h"
#include "DataAccess/UsuarioDAO.h"
#include "FormsLogin/formUsuario.h"
#include "FormsLogin/formBoasVindas.h"
#include "FormsLogin/formLoginSenha.h"
#include "FormsDashboard/formMainDashboard.h"
#include "Designer/Gerenciamento/SessionManager.h"
#include <QSettings>
#include <QMessageBox>
#include <QDebug>

formInicio::formInicio(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::formInicio)
{
    ui->setupUi(this);
    m_formUsuario = nullptr;

    connect(ui->buttonAppAcess, &QPushButton::clicked, this, &formInicio::tentarLogin);
    connect(ui->buttonSwitchUsuario, &QPushButton::clicked, this, &formInicio::abrirTelaSelecaoUsuario);
    connect(ui->buttonExit, &QPushButton::clicked, this, &QApplication::quit);

    // Inicia a busca pelo usuário inicial via API
    ui->buttonAppAcess->setText("Carregando...");
    ui->buttonAppAcess->setEnabled(false);

    UsuarioDAO *dao = new UsuarioDAO(this);
    connect(dao, &UsuarioDAO::usuarioInicialRecebido, this, &formInicio::onUsuarioInicialRecebido);
    connect(dao, &UsuarioDAO::erroDeRede, this, [=](const QString& erro){
        QMessageBox::critical(this, "Erro de Rede", erro);
    });
    dao->obterUsuarioInicial(); // Dispara a requisição
}

formInicio::~formInicio()
{
    delete ui;
}

// Slot chamado quando o DAO responde com o usuário inicial
void formInicio::onUsuarioInicialRecebido(const std::optional<Usuario>& usuario)
{
    if (usuario) {
        // Se um usuário foi encontrado, atualiza o botão e a variável membro
        m_usuarioAtual = *usuario;
        ui->buttonAppAcess->setText(m_usuarioAtual->nomeUsuario);
        ui->buttonAppAcess->setEnabled(true);
    } else {
        // Se o backend não retornou nenhum usuário, vamos para a tela de boas-vindas
        formBoasVindas *janelaBoasVindas = new formBoasVindas(this); // O construtor de boas-vindas também deve ser simplificado
        janelaBoasVindas->show();
        this->close();
    }
}

// Slot chamado quando o usuário clica no botão principal para logar
void formInicio::tentarLogin()
{
    if (!m_usuarioAtual) {
        QMessageBox::warning(this, "Aguarde", "Carregando informações do usuário.");
        return;
    }

    // Abre o diálogo de senha, que também foi refatorado para usar a API
    formLoginSenha *dialogoSenha = new formLoginSenha(*m_usuarioAtual, this);
    dialogoSenha->setAttribute(Qt::WA_DeleteOnClose);
    // Conectamos o sinal de sucesso do diálogo a um slot aqui
    connect(dialogoSenha, &formLoginSenha::loginSucesso, this, &formInicio::onLoginSucesso);
    dialogoSenha->open(); // Usamos open() para não bloquear
}

// Slot chamado quando o login no formLoginSenha é bem-sucedido
void formInicio::onLoginSucesso(const QString& token, const Usuario& usuario)
{
    qDebug() << "Login bem-sucedido na formInicio! Token recebido:" << token;

    // Guardar o token e os dados do usuário em um SessionManager seria o ideal aqui
    // SessionManager::instance().setToken(token);
    // SessionManager::instance().setUsuarioLogado(usuario);

    // Abre o dashboard principal
    formMainDashboard *dashboard = new formMainDashboard(); // O dashboard também será refatorado
    dashboard->showMaximized();
    this->close();
}


void formInicio::abrirTelaSelecaoUsuario()
{
    if (!m_formUsuario) {
        m_formUsuario = new formUsuario(SessionManager::instance().getToken(), this); // Construtor simplificado
        m_formUsuario->setAttribute(Qt::WA_DeleteOnClose);

        // Conecta o sinal do usuário selecionado ao nosso slot de atualização
        connect(m_formUsuario, &formUsuario::usuarioSelecionado, this, &formInicio::onUsuarioSelecionado);

        // Conecta o sinal de fechamento para simplesmente reaparecer
        connect(m_formUsuario, &formUsuario::fechado, this, &QWidget::show);
    }
    this->hide();
    m_formUsuario->show();
}

// Slot chamado quando um usuário é escolhido na tela de seleção
void formInicio::onUsuarioSelecionado(const Usuario& usuario)
{
    m_usuarioAtual = usuario;
    ui->buttonAppAcess->setText(m_usuarioAtual->nomeUsuario);
    // Salva a nova preferência no QSettings
    QSettings settings("BrunoApps", "MeuCentavoApp");
    settings.setValue("ultimoUsuarioId", usuario.id);
    this->show(); // Reexibe a formInicio, que já está escondida
}

void formInicio::onLoginFalhou(const QString& motivo)
{
    // Simplesmente mostra uma caixa de mensagem com o erro recebido da API.
    QMessageBox::warning(this, "Falha no Login", motivo);
}