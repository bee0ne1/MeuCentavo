//
// Created by bruno on 07/07/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_formLoginSenha.h" resolved

#include "formLoginSenha.h"
#include "ui_formLoginSenha.h"
#include "DataAccess/UsuarioDAO.h"
#include <QMessageBox>
#include <QCryptographicHash> // Para o Hashing da senha


formLoginSenha::formLoginSenha(const Usuario& usuario, QSqlDatabase db, QWidget *parent) :
    QDialog(parent), ui(new Ui::formLoginSenha), m_db(db),m_usuario(usuario) {
    ui->setupUi(this);
    m_passwordHelper = new PasswordFormHelper(ui->lineEditSenha, ui->buttonViewPassword, this);
    setWindowTitle("Autenticação");

    // Personaliza a mensagem de prompt
    ui->labelPrompt->setText(QString("Senha para %1:").arg(m_usuario.nomeUsuario));

    // O botão Cancelar simplesmente "rejeita" e fecha o diálogo
    connect(ui->buttonCancelar, &QPushButton::clicked, this, &QDialog::reject);
}

formLoginSenha::~formLoginSenha() {
    delete ui;
}

void formLoginSenha::on_buttonEntrar_clicked()
{
    QString senhaDigitada = ui->lineEditSenha->text();

    // Lógica de autenticação do DAO (precisamos criar/ajustar este método)
    UsuarioDAO dao(m_db);

    // Supondo que temos um método que verifica a senha de um usuário específico
    if (dao.verificarSenhaUsuario(m_usuario.id, senhaDigitada)) {
        // Se a senha estiver correta, "aceitamos" e fechamos o diálogo.
        // Isso fará com que dialog.exec() retorne QDialog::Accepted.
        this->accept();
    } else {
        // Se a senha estiver errada, mostramos um aviso.
        QMessageBox::warning(this, "Erro de Autenticação", "Senha incorreta.");
        ui->lineEditSenha->clear(); // Limpa o campo para nova tentativa
    }
}