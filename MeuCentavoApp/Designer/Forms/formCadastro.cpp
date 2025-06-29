#include "formCadastro.h"
#include "ui_formCadastro.h"
#include "formUsuario.h"
#include "Negocio/UsuarioDAO.h"
#include "Modelo/Usuario.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>

formCadastro::formCadastro(formUsuario *usuario,QSqlDatabase db,QWidget *parent)
    : QWidget(parent),
      ui(new Ui::formCadastro),
    usuarioWindow(usuario),
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
    usuarioWindow->show();
}

void formCadastro::gravarUsuario()
{
    // a. Pega os dados da interface
    QString nome = ui->lineEditUsuario->text();
    QString senha = ui->lineEditSenha->text();

    // b. Cria a struct Usuario e a preenche
    Usuario novoUsuario;
    novoUsuario.nomeUsuario = nome;
    novoUsuario.senha = senha;

    // c. Cria o DAO e tenta inserir no banco
    UsuarioDAO dao(m_db); // Usa a conexão que guardamos

    if (dao.adicionarUsuario(novoUsuario)) {
        // Se deu certo, avisa o usuário e volta para a tela anterior
        QMessageBox::information(this, "Sucesso", "Usuário cadastrado com sucesso!");
        cancelarCadastro(); // Reutiliza a função de fechar e mostrar a outra tela
    } else {
        // Se deu errado, avisa o usuário
        QMessageBox::warning(this, "Erro de Cadastro",
                             "Não foi possível cadastrar o usuário.\n"
                             "O nome de usuário pode já estar em uso.");
    }
}
