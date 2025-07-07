#include "formCadastro.h"
#include "ui_formCadastro.h"
#include "formUsuario.h"
#include "DataAccess/UsuarioDAO.h"
#include "Modelo/Usuario.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QCryptographicHash>


formCadastro::formCadastro(QSqlDatabase db,QWidget *parent):
    QWidget(parent),
    ui(new Ui::formCadastro),
    m_db(db) // <-- INICIALIZE A VARIÁVEL DO BANCO

{
    ui->setupUi(this);
    m_passwordHelper = new PasswordFormHelper(ui->lineEditSenha, ui->buttonViewPassword, this);
    connect(ui->lineEditSenha, &QLineEdit::textChanged, this, &formCadastro::verificarCampos);
    connect(ui->lineEditUsuario, &QLineEdit::textChanged, this, &formCadastro::verificarCampos);
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


void formCadastro::cancelarCadastro() {
    this->close();
}

void formCadastro::gravarUsuario()
{

    // Pega os dados da interface
    QString nome = ui->lineEditUsuario->text();
    QString senhaDigitada = ui->lineEditSenha->text();

    // Validação de complexidade da senha (ainda recomendada)
    if (senhaDigitada.length() < 6) {
        QMessageBox::warning(this, "Senha Fraca", "A senha deve ter pelo menos 6 caracteres.");
        return;
    }

    // Validação de usuário duplicado no banco
    UsuarioDAO dao(m_db);
    if (dao.existeUsuario(nome)) {
        QMessageBox::warning(this, "Erro de Cadastro", "Este nome de usuário já está em uso.");
        return;
    }

    // Gera o hash da senha pura usando o algoritmo SHA-256
    QByteArray hashBytes = QCryptographicHash::hash(senhaDigitada.toUtf8(), QCryptographicHash::Sha256);
    // Converte o hash para uma string hexadecimal para salvar no banco
    QString senhaComHash = hashBytes.toHex();


    // Se todas as validações passaram, cria e salva o usuário
    Usuario novoUsuario;
    novoUsuario.nomeUsuario = nome;
    novoUsuario.senha = senhaComHash;

    if (dao.adicionarUsuario(novoUsuario)) {
        QMessageBox::information(this, "Sucesso", "Usuário cadastrado com sucesso!");
        emit cadastroConcluido();
        this->close();
    } else {
        QMessageBox::warning(this, "Erro de Banco de Dados", "Ocorreu um erro inesperado ao salvar o usuário.");
    }
}
