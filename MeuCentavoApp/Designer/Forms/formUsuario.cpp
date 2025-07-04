//
// Created by bruno on 18/06/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_formUsuario.h" resolved

#include "formUsuario.h"
#include "ui_formUsuario.h"
#include "formCadastro.h"
#include "DataAccess/UsuarioDAO.h"
#include <QDebug>
#include <QCloseEvent>
#include <QPushButton>
#include <QLayoutItem>
#include "formExcluirUsuario.h"

formUsuario::formUsuario(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::formUsuario),
    m_db(db)
{
    ui->setupUi(this);

    connect(ui->buttonCadastro, &QPushButton::clicked, this, &formUsuario::abrirFormCadastro);
    connect(ui->buttonBack, &QPushButton::clicked, this, &formUsuario::voltarFormInicio);
    connect(ui-> buttonExcluirUsuarios, &QPushButton::clicked, this, &formUsuario:: abrirExcluirUsuarios);
    carregarListaDeUsuarios();
}

formUsuario::~formUsuario()
{
    delete ui;
}

void formUsuario::closeEvent(QCloseEvent *event)
{
    emit usuarioFechado();
    QWidget::closeEvent(event);
}

void formUsuario::abrirFormCadastro()
{
    if (!cadastroWindow) {
        cadastroWindow = new formCadastro(m_db, nullptr);
        cadastroWindow->setAttribute(Qt::WA_DeleteOnClose);

        // --- ESTA É A LINHA QUE FAZ A MÁGICA DO REFRESH ---
        // Ela conecta o sinal do cadastro à função que atualiza a lista.
        connect(cadastroWindow, &formCadastro::cadastroConcluido,
                this, &formUsuario::carregarListaDeUsuarios);
        // ----------------------------------------------------

        // Conexão para a navegação de volta
        connect(cadastroWindow, &QObject::destroyed, [this]() {
            this->show();
            this->cadastroWindow = nullptr;
        });
    }
    cadastroWindow->show();


}


void formUsuario::voltarFormInicio()
{
    this->close();
}

void formUsuario::carregarListaDeUsuarios()
{
    qDebug() << "Carregando a lista de usuários para a UI...";
    QLayoutItem* item;
    while ((item = ui->layoutUsuarios->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    UsuarioDAO dao(m_db);
    QVector<Usuario> usuarios = dao.obterTodosUsuarios();

    for (const auto& usuario : usuarios) {
        QPushButton *botaoUsuario = new QPushButton(usuario.nomeUsuario, this);
        botaoUsuario->setMinimumHeight(40);
        botaoUsuario->setCursor(Qt::PointingHandCursor);

        connect(botaoUsuario, &QPushButton::clicked, [this, usuario]() {
            qDebug() << "Usuário selecionado:" << usuario.nomeUsuario;
            emit usuarioAtual(usuario);
        });
        ui->layoutUsuarios->addWidget(botaoUsuario);
    }
}

void formUsuario::abrirExcluirUsuarios()
{
    if (!excluirWindow)
    {
        excluirWindow = new formExcluirUsuario(m_db, nullptr);
        excluirWindow->setAttribute(Qt::WA_DeleteOnClose);
         // Conecta o sinal de modificação da janela filha à função que
         // recarrega a lista de botões desta janela (a mãe).
        connect(excluirWindow, &formExcluirUsuario::listaDeUsuariosModificada,
                this, &formUsuario::carregarListaDeUsuarios);
        // Conexão para a navegação de volta
        connect(excluirWindow, &formExcluirUsuario::exclusaoFechada, [this]() {
            this->show();
        });

        connect(excluirWindow, &QObject::destroyed, [this]() {
            this->excluirWindow = nullptr;
        });

    }
    excluirWindow->show();
}

