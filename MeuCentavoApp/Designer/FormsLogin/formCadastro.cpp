#include "formCadastro.h"
#include "ui_formCadastro.h"
#include "DataAccess/UsuarioDAO.h" // Inclui nosso DAO refatorado
#include <QMessageBox>
#include <QDebug>

formCadastro::formCadastro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formCadastro)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Cadastrar Novo Usuário");

    // Cria o ajudante para a funcionalidade de "visualizar senha"
    m_passwordHelper = new PasswordFormHelper(ui->lineEditSenha, ui->buttonViewPassword, this);

    // Conecta os botões e campos de texto
    connect(ui->lineEditSenha, &QLineEdit::textChanged, this, &formCadastro::verificarCampos);
    connect(ui->lineEditUsuario, &QLineEdit::textChanged, this, &formCadastro::verificarCampos);
    connect(ui->buttonCancelar, &QPushButton::clicked, this, &QWidget::close); // Botão cancelar simplesmente fecha a janela
    connect(ui->buttonGravarUsuario, &QPushButton::clicked, this, &formCadastro::gravarUsuario);

    verificarCampos(); // Garante que o botão de gravar comece desabilitado
}

formCadastro::~formCadastro()
{
    delete ui;
}

void formCadastro::verificarCampos()
{
    bool usuarioPreenchido = !ui->lineEditUsuario->text().isEmpty();
    bool senhaPreenchida   = !ui->lineEditSenha->text().isEmpty();
    ui->buttonGravarUsuario->setEnabled(usuarioPreenchido && senhaPreenchida);
}

void formCadastro::gravarUsuario()
{
    QString nome = ui->lineEditUsuario->text();
    QString senha = ui->lineEditSenha->text();

    // Validação de UI: complexidade da senha
    if (senha.length() < 6) {
        QMessageBox::warning(this, "Senha Fraca", "A senha deve ter pelo menos 6 caracteres.");
        return;
    }

    // Desabilita o botão para evitar cliques duplos enquanto espera a resposta da rede
    ui->buttonGravarUsuario->setEnabled(false);
    ui->buttonGravarUsuario->setText("Salvando...");

    // Cria uma instância do nosso DAO (que agora é um cliente de API)
    UsuarioDAO *dao = new UsuarioDAO(this);

    // Conecta os sinais de resultado do DAO aos nossos novos slots
    connect(dao, &UsuarioDAO::registroSucesso, this, &formCadastro::onRegistroSucesso);
    connect(dao, &UsuarioDAO::registroFalhou, this, &formCadastro::onRegistroFalhou);

    // Inicia a requisição de rede para registrar o usuário
    dao->registrarUsuario(nome, senha);
}

void formCadastro::onRegistroSucesso()
{
    // O DAO nos avisou que a API retornou sucesso!
    QMessageBox::information(this, "Sucesso", "Usuário cadastrado com sucesso!");
    emit cadastroConcluido(); // Avisa a janela anterior sobre o sucesso
    this->close(); // Fecha a janela de cadastro
}

void formCadastro::onRegistroFalhou(const QString& motivo)
{
    // O DAO nos avisou que a API retornou um erro
    QMessageBox::warning(this, "Erro de Cadastro", motivo);

    // Reabilita o botão para o usuário poder tentar novamente
    ui->buttonGravarUsuario->setEnabled(true);
    ui->buttonGravarUsuario->setText("Gravar Usuário");
}