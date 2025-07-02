#include "formMain.h"
#include "ui_formMain.h"
#include "Forms/formUsuario.h"  // Inclui as definições das janelas que vai abrir
#include <QDebug>
#include "DataAccess//UsuarioDAO.h" // Precisa do DAO para buscar

formMain::formMain(QSqlDatabase db, QWidget *parent):
    QMainWindow(parent), ui(new Ui::formMain), m_db(db){
    ui->setupUi(this);
    connect(ui->buttonSwitchUsuario, &QPushButton::clicked, this, &formMain::abrirTelaUsuario);
    connect(ui->buttonExit, &QPushButton::clicked, this, &QApplication::quit);

    // Chama a função para personalizar a UI
    atualizarBoasVindas();
    carregarUltimoUsuario();
}

formMain::~formMain() {
    delete ui;
}
void formMain::carregarUltimoUsuario()
{
    qDebug() << "formMain: Atualizando o último usuário...";
    UsuarioDAO dao(m_db);

    // O método obterUltimoUsuario() que criamos agora será usado.
    if (auto ultimoUsuarioOpt = dao.obterUltimoUsuario()) {
        // Supondo que o botão principal se chama 'buttonUltimoUsuario'
        ui->buttonAppAcess->setText(ultimoUsuarioOpt->nomeUsuario);
    } else {
        ui->buttonAppAcess->setText("Cadastrar Usuário");
    }
}

void formMain::abrirTelaUsuario() {

    if (!usuarioWindow) {
        usuarioWindow = new formUsuario(m_db, nullptr);

        // --- CONEXÃO ATUALIZADA ---
        // Agora, quando o sinal 'usuarioFechado' for emitido, executamos uma pequena
        // função (lambda) que faz DUAS coisas:
        connect(usuarioWindow, &formUsuario::usuarioFechado, [this]() {
            // 1. Reexibe a janela principal
            this->show();
            // 2. Chama a função para recarregar o último usuário do banco
            this->carregarUltimoUsuario();
            // 3. Limpa o ponteiro para que a janela possa ser recriada na próxima vez
            this->usuarioWindow = nullptr;
        });
    }

    this->hide();
    usuarioWindow->show();
}

void formMain::atualizarBoasVindas()
{
    // Supondo que você tenha um QLabel no seu formMain.ui chamado 'labelBoasVindas'
    // Você pode usar HTML simples para formatar o texto.
    QString texto = QString("Olá, <b>%1</b>!").arg(m_usuarioAtual.nomeUsuario);
    ui->buttonAppAcess->setText(texto);
}

