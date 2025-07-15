#include "formLoginSenha.h"
#include "ui_formLoginSenha.h"
#include "DataAccess/UsuarioDAO.h"
#include <QMessageBox>
#include <QDebug>

formLoginSenha::formLoginSenha(const Usuario& usuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formLoginSenha),
    m_usuario(usuario) // Armazena o usuário recebido
{
    ui->setupUi(this);
    setWindowTitle("Autenticação");

    // Cria o ajudante para a funcionalidade de "visualizar senha"
    m_passwordHelper = new PasswordFormHelper(ui->lineEditSenha, ui->buttonViewPassword, this);

    // Personaliza a mensagem de prompt para o usuário
    ui->labelPrompt->setText(QString("Senha para %1:").arg(m_usuario.nomeUsuario));

    // Conecta os botões
    connect(ui->buttonEntrar, &QPushButton::clicked, this, &formLoginSenha::tentarLogin);
    connect(ui->buttonCancelar, &QPushButton::clicked, this, &QDialog::reject);
}

formLoginSenha::~formLoginSenha()
{
    delete ui;
}

void formLoginSenha::tentarLogin()
{
    QString senhaDigitada = ui->lineEditSenha->text();
    if (senhaDigitada.isEmpty()) {
        QMessageBox::warning(this, "Campo Vazio", "Por favor, digite sua senha.");
        return;
    }

    // Desabilita o botão para evitar cliques duplos
    ui->buttonEntrar->setEnabled(false);
    ui->buttonEntrar->setText("Verificando...");

    // Cria uma instância do nosso DAO de rede
    UsuarioDAO *dao = new UsuarioDAO(this);

    // Conecta os sinais de resultado do DAO aos nossos slots
    connect(dao, &UsuarioDAO::loginSucesso, this, &formLoginSenha::onLoginSucesso);
    connect(dao, &UsuarioDAO::erroDeAutenticacao, this, &formLoginSenha::onLoginFalhou);
    connect(dao, &UsuarioDAO::erroDeRede, this, &formLoginSenha::onLoginFalhou); // Podemos usar o mesmo slot de falha

    // Inicia a requisição de rede para logar o usuário
    dao->logarUsuario(m_usuario.nomeUsuario, senhaDigitada);
}

void formLoginSenha::onLoginSucesso(const QString& token, const Usuario& usuario)
{
    // O DAO nos avisou que a API retornou sucesso!
    qDebug() << "Diálogo de senha: Login bem-sucedido.";

    // Emitimos nosso próprio sinal para avisar a formInicio, passando os dados adiante.
    emit loginSucesso(token, usuario);

    // Fecha o diálogo com o status de "Aceito".
    this->accept();
}

void formLoginSenha::onLoginFalhou(const QString& motivo)
{
    // O DAO nos avisou que a API retornou um erro.
    QMessageBox::warning(this, "Erro de Autenticação", motivo);

    // Reabilita o botão para o usuário poder tentar novamente.
    ui->buttonEntrar->setEnabled(true);
    ui->buttonEntrar->setText("Entrar");
    ui->lineEditSenha->clear();
    ui->lineEditSenha->setFocus();
}