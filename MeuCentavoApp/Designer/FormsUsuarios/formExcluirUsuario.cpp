#include "formExcluirUsuario.h"
#include "ui_formExcluirUsuario.h"
#include "DataAccess/UsuarioDAO.h"
#include <QPushButton>
#include <QLayoutItem>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>

formExcluirUsuario::formExcluirUsuario(const QString& token, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::formExcluirUsuario),
    m_token(token)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Excluir Usuário");

    // Cria uma única instância do DAO para esta janela
    m_dao = new UsuarioDAO(this);

    // Conecta os sinais de resultado do DAO aos nossos slots
    connect(m_dao, &UsuarioDAO::todosUsuariosRecebidos, this, &formExcluirUsuario::onUsuariosRecebidos);
    connect(m_dao, &UsuarioDAO::remocaoSucesso, this, &formExcluirUsuario::onRemocaoSucesso);
    connect(m_dao, &UsuarioDAO::erroDeRede, this, &formExcluirUsuario::onErro);
    connect(m_dao, &UsuarioDAO::erroDeAutenticacao, this, &formExcluirUsuario::onErro); // Podemos usar o mesmo slot de erro

    connect(ui->buttonVoltar, &QPushButton::clicked, this, &QWidget::close);

    // Inicia a busca pelos usuários
    carregarUsuarios();
}

formExcluirUsuario::~formExcluirUsuario()
{
    delete ui;
}

void formExcluirUsuario::closeEvent(QCloseEvent *event)
{
    emit exclusaoFechada();
    QWidget::closeEvent(event);
}

void formExcluirUsuario::carregarUsuarios()
{
    qDebug() << "Requisitando lista de usuários da API...";
    // Inicia a requisição de rede e "esquece". A resposta virá no slot 'onUsuariosRecebidos'.
    m_dao->obterTodosUsuarios(m_token);
}

void formExcluirUsuario::onUsuariosRecebidos(const QVector<Usuario>& usuarios)
{
    qDebug() << "Lista de usuários recebida, atualizando interface.";
    // Limpa o layout antes de adicionar os novos botões
    QLayoutItem* item;
    while ((item = ui->layoutUsuariosExcluir->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Cria os botões com base na lista recebida da API
    for (const auto& usuario : usuarios) {
        QPushButton *botaoUsuario = new QPushButton(usuario.nomeUsuario, this);
        botaoUsuario->setMinimumHeight(40);
        botaoUsuario->setCursor(Qt::PointingHandCursor);

        connect(botaoUsuario, &QPushButton::clicked, this, [this, usuario]() {
            confirmarExclusaoUsuario(usuario);
        });
        ui->layoutUsuariosExcluir->addWidget(botaoUsuario);
    }
}

void formExcluirUsuario::confirmarExclusaoUsuario(const Usuario& usuario)
{
    QMessageBox::StandardButton resposta = QMessageBox::question(this, "Confirmar Exclusão",
        QString("Tem certeza que deseja excluir o usuário '%1'?").arg(usuario.nomeUsuario),
        QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        qDebug() << "Enviando requisição para remover o usuário ID:" << usuario.id;
        // Inicia a requisição de rede para remover o usuário. A resposta virá no slot 'onRemocaoSucesso' ou 'onErro'.
        m_dao->removerUsuario(usuario.id, m_token);
    }
}

void formExcluirUsuario::onRemocaoSucesso()
{
    qDebug() << "DAO informou que a remoção foi um sucesso.";
    QMessageBox::information(this, "Sucesso", "Usuário removido com sucesso.");

    // Após remover, requisita a lista de usuários novamente para atualizar a tela
    carregarUsuarios();

    // Avisa o resto da aplicação que a lista de usuários mudou
    emit listaDeUsuariosModificada();
}

void formExcluirUsuario::onErro(const QString& motivo)
{
    QMessageBox::warning(this, "Erro", motivo);
}