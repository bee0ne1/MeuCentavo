//
// Created by bruno on 01/07/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_formExcluirUsuario.h" resolved

#include "formExcluirUsuario.h"
#include "ui_formExcluirUsuario.h"
#include "DataAccess/UsuarioDAO.h"
#include <QPushButton>
#include <QLayoutItem>
#include <QMessageBox> // Essencial para a janela de confirmação
#include <QCloseEvent>
#include <QDebug>


formExcluirUsuario::formExcluirUsuario(QSqlDatabase db,QWidget *parent) :
     QWidget(parent), ui(new Ui::formExcluirUsuario), m_db(db) {
     ui->setupUi(this);
     setAttribute(Qt::WA_DeleteOnClose);
    //
    // Conecta o botão de voltar para simplesmente fechar a janela
     connect(ui->buttonVoltar, &QPushButton::clicked, this, &QWidget::close);
    //
    // Carrega a lista de usuários assim que a janela é criada
    carregarUsuarios();
}



formExcluirUsuario::~formExcluirUsuario() {
    delete ui;
}

void formExcluirUsuario::closeEvent(QCloseEvent *event)
{
    emit exclusaoFechada(); // Avisa a janela mãe que estamos fechando
    QWidget::closeEvent(event);
}

void formExcluirUsuario::carregarUsuarios()
{
    qDebug() << "Carregando usuários para exclusão...";
    // Limpa o layout antes de adicionar os novos botões
    QLayoutItem* item;
    while ((item = ui->layoutUsuariosExcluir->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    UsuarioDAO dao(m_db);
    QVector<Usuario> usuarios = dao.obterTodosUsuarios();

    for (const auto& usuario : usuarios) {
        QPushButton *botaoUsuario = new QPushButton(usuario.nomeUsuario, this);
        botaoUsuario->setMinimumHeight(40);
        botaoUsuario->setCursor(Qt::PointingHandCursor);

        // Conecta o clique de cada botão à função de confirmação
        connect(botaoUsuario, &QPushButton::clicked, this, [this, usuario]() {
            confirmarExclusaoUsuario(usuario);
        });

        ui->layoutUsuariosExcluir->addWidget(botaoUsuario);
    }
}

void formExcluirUsuario::confirmarExclusaoUsuario(const Usuario& usuario)
{
    // Usa uma QMessageBox padrão do Qt para perguntar ao usuário
    QMessageBox::StandardButton resposta = QMessageBox::question(this, "Confirmar Exclusão",
        QString("Tem certeza que deseja excluir o usuário '%1'?\nEsta ação não pode ser desfeita.").arg(usuario.nomeUsuario),
        QMessageBox::Yes | QMessageBox::No);

    // Se o usuário clicou em "Sim"...
    if (resposta == QMessageBox::Yes) {
        UsuarioDAO dao(m_db);
        if (dao.removerUsuario(usuario.id)) {
            QMessageBox::information(this, "Sucesso", "Usuário removido com sucesso.");
            // Após remover, recarrega a lista de botões para refletir a mudança
            carregarUsuarios();
            // Avisa o resto da aplicação que a lista de usuários mudou
            emit listaDeUsuariosModificada();
        } else {
            QMessageBox::warning(this, "Erro", "Não foi possível remover o usuário.");
        }
    }
}