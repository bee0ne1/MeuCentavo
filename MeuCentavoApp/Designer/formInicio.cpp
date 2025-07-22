#include "formInicio.h"
#include "ui_formInicio.h"
#include "DataAccess/UsuarioDAO.h"
#include "FormsUsuarios/formUsuario.h"
#include "FormsUsuarios/formBoasVindas.h"
#include "FormsUsuarios/formLoginSenha.h"
#include "FormsDashboard/formMainDashboard.h"
#include "Gerenciamento/SessionManager.h"
#include <QSettings>
#include <QMessageBox>
#include <QDebug>

formInicio::formInicio(const Usuario& usuarioInicial, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::formInicio),
    m_usuarioAtual(usuarioInicial)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->buttonExit, &QPushButton::clicked, this, &QApplication::quit);

    qDebug() << "formInicio: Exibindo o usuário recebido:" << m_usuarioAtual.nomeUsuario;
    ui->buttonAppAcess->setText(m_usuarioAtual.nomeUsuario);

}

formInicio::~formInicio()
{
    delete ui;
}

// Slot chamado quando o usuário clica no botão principal para logar.
void formInicio::on_buttonAppAcess_clicked()
{
    // Cria e abre o diálogo de senha para o usuário atual.
    formLoginSenha* dialogoSenha = new formLoginSenha(m_usuarioAtual, this);
    dialogoSenha->setAttribute(Qt::WA_DeleteOnClose);

    // Conecta o sinal de sucesso do diálogo ao nosso próprio slot.
    connect(dialogoSenha, &formLoginSenha::loginSucesso, this, &formInicio::onLoginFinalizado);

    // Usa .open() para não bloquear o loop de eventos da aplicação.
    dialogoSenha->open();
}

// Slot chamado quando o diálogo de senha emite o sinal de sucesso.
void formInicio::onLoginFinalizado(const QString& token, const Usuario& usuario)
{
    qDebug() << "formInicio: Login bem-sucedido. Avisando o AppController.";

    // A única responsabilidade desta janela é repassar a informação para o controlador.
    emit loginBemSucedido(token, usuario);
}
