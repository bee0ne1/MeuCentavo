#include "formUsuario.h"
#include "ui_formUsuario.h"
#include "formCadastro.h"
#include "formExcluirUsuario.h"
#include "DataAccess/UsuarioDAO.h"
#include "Gerenciamento/SessionManager.h"
#include <QPushButton>
#include <QLayoutItem>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>

formUsuario::formUsuario(const QString& token, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::formUsuario),
    m_token(token)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Selecionar ou Gerenciar Usuários");

    m_formCadastro = nullptr;
    m_formExcluirUsuario = nullptr;

    // Cria uma única instância do DAO para esta janela
    m_dao = new UsuarioDAO(this);

    // Conecta os sinais de resultado do DAO aos nossos slots
    connect(m_dao, &UsuarioDAO::todosUsuariosRecebidos, this, &formUsuario::onUsuariosRecebidos);
    connect(m_dao, &UsuarioDAO::erroDeRede, this, &formUsuario::onErroDeRede);
    // Você pode conectar outros sinais do DAO aqui se precisar (ex: de exclusão)

    // Conecta os botões da interface
    connect(ui->buttonCadastro, &QPushButton::clicked, this, &formUsuario::abrirTelaCadastro);
    connect(ui->buttonExcluirUsuarios, &QPushButton::clicked, this, &formUsuario::abrirTelaExcluir);
    connect(ui->buttonBack, &QPushButton::clicked, this, &QWidget::close);

    // Inicia a busca pelos usuários assim que a janela é criada
    carregarListaDeUsuarios();
}

formUsuario::~formUsuario()
{
    delete ui;
}

void formUsuario::closeEvent(QCloseEvent *event)
{
    emit fechado(); // Emite o sinal para a formInicio saber que foi fechado
    QWidget::closeEvent(event);
}

void formUsuario::carregarListaDeUsuarios()
{
    qDebug() << "formUsuario: Requisitando lista de usuários da API...";
    ui->labelStatus->setText("Carregando..."); // Opcional: um label de status na UI
    // Inicia a requisição de rede e espera a resposta chegar no slot onUsuariosRecebidos
    m_dao->obterTodosUsuarios(m_token);
}

void formUsuario::onUsuariosRecebidos(const QVector<Usuario>& usuarios)
{
    qDebug() << "formUsuario: Lista com" << usuarios.count() << "usuários recebida. Atualizando UI.";
    ui->labelStatus->setText("Selecione um usuário:");

    // Limpa o layout antes de adicionar os novos botões
    QLayoutItem* item;
    while ((item = ui->layoutUsuarios->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Cria os botões com base na lista recebida da API
    for (const auto& usuario : usuarios) {
        QPushButton *botaoUsuario = new QPushButton(usuario.nomeUsuario, this);
        botaoUsuario->setMinimumHeight(40);
        botaoUsuario->setCursor(Qt::PointingHandCursor);

        connect(botaoUsuario, &QPushButton::clicked, this, [this, usuario]() {
            qDebug() << "Usuário selecionado:" << usuario.nomeUsuario;
            SessionManager::instance().trocarUsuario(usuario);
            // O AppController irá capturar o sinal do SessionManager e fechará
            // todas as janelas (incluindo esta e a dashboard) para reiniciar o fluxo.
        });
        ui->layoutUsuarios->addWidget(botaoUsuario);
    }
}

void formUsuario::abrirTelaCadastro()
{
    if (!m_formCadastro) {
        // O formCadastro também foi refatorado e não precisa mais do 'db'
        m_formCadastro = new formCadastro(this);
        m_formCadastro->setAttribute(Qt::WA_DeleteOnClose);

        // Quando um cadastro for concluído, recarregamos a lista de usuários
        connect(m_formCadastro, &formCadastro::cadastroConcluido, this, &formUsuario::carregarListaDeUsuarios);
    }
    m_formCadastro->show();
}

void formUsuario::abrirTelaExcluir()
{
    if (!m_formExcluirUsuario) {
        m_formExcluirUsuario = new formExcluirUsuario(m_token, nullptr);

        // Define que esta janela bloqueará todas as outras da aplicação.
        m_formExcluirUsuario->setWindowModality(Qt::ApplicationModal);

        connect(m_formExcluirUsuario, &formExcluirUsuario::listaDeUsuariosModificada, this, &formUsuario::carregarListaDeUsuarios);
        // Também é uma boa prática limpar o ponteiro quando a janela for fechada
        connect(m_formExcluirUsuario, &QObject::destroyed, this, [this](){
            m_formExcluirUsuario = nullptr;
            this->show();
        });
    }
    this->hide();
    m_formExcluirUsuario->show();
}

void formUsuario::onErroDeRede(const QString& motivo)
{
    QMessageBox::critical(this, "Erro de Rede", motivo);
    ui->labelStatus->setText("Erro ao carregar usuários.");
}