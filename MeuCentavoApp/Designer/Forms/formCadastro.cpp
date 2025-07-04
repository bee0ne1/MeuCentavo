#include "formCadastro.h"
#include "ui_formCadastro.h"
#include "formUsuario.h"
#include "DataAccess/UsuarioDAO.h"
#include "Modelo/Usuario.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>

formCadastro::formCadastro(QSqlDatabase db,QWidget *parent):
    QWidget(parent),
    ui(new Ui::formCadastro),
    m_db(db) // <-- INICIALIZE A VARIÁVEL DO BANCO

{
    ui->setupUi(this);
    connect(ui->lineEditSenha, &QLineEdit::textChanged, this, &formCadastro::verificarCampos);
    connect(ui->lineEditUsuario, &QLineEdit::textChanged, this, &formCadastro::verificarCampos);
    connect(ui->buttonViewPassword, &QPushButton::clicked, this, &formCadastro::visualizarSenha);
    connect(ui->buttonCancelar, &QPushButton::clicked, this, &formCadastro::cancelarCadastro);
    connect(ui->buttonGravarUsuario, &QPushButton::clicked, this, &formCadastro::gravarUsuario);

    // Chame isso para garantir que o botão comece desabilitado
    verificarCampos();
}

formCadastro::~formCadastro() {
    delete ui;
}

void formCadastro::closeEvent(QCloseEvent *event) {
    qDebug() << "formCadastro sendo fechado";
    emit cadastroFechado();
    QWidget::closeEvent(event);
}

void formCadastro::verificarCampos() {
    bool usuarioPreenchido = !ui->lineEditUsuario->text().isEmpty();
    bool senhaPreenchida   = !ui->lineEditSenha->text().isEmpty();

    ui->buttonGravarUsuario->setEnabled(usuarioPreenchido && senhaPreenchida);
}

void formCadastro::visualizarSenha() {
    bool senhaEscondida = ui->lineEditSenha->echoMode() == QLineEdit::Password;

    ui->lineEditSenha->setEchoMode(senhaEscondida ? QLineEdit::Normal : QLineEdit::Password);
}

void formCadastro::cancelarCadastro() {
    this->close();
}

void formCadastro::gravarUsuario()
{

    // a. Pega os dados da interface
    QString nome = ui->lineEditUsuario->text();
    QString senha = ui->lineEditSenha->text();

    // b. Validação de complexidade da senha (ainda recomendada)
    if (senha.length() < 6) {
        QMessageBox::warning(this, "Senha Fraca", "A senha deve ter pelo menos 6 caracteres.");
        return;
    }

    // c. Validação de usuário duplicado no banco
    UsuarioDAO dao(m_db);
    if (dao.existeUsuario(nome)) {
        QMessageBox::warning(this, "Erro de Cadastro", "Este nome de usuário já está em uso.");
        return;
    }

    // d. Se todas as validações passaram, cria e salva o usuário
    Usuario novoUsuario;
    novoUsuario.nomeUsuario = nome;
    novoUsuario.senha = senha;

    if (dao.adicionarUsuario(novoUsuario)) {
        QMessageBox::information(this, "Sucesso", "Usuário cadastrado com sucesso!");
        emit cadastroConcluido();
        this->close();
    } else {
        QMessageBox::warning(this, "Erro de Banco de Dados", "Ocorreu um erro inesperado ao salvar o usuário.");
    }
}
