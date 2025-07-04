#include "formInicio.h"
#include "ui_formInicio.h"
#include "Forms/formUsuario.h"
#include "Forms/formBoasVindas.h"
#include <QDebug>
#include "DataAccess//UsuarioDAO.h"
#include <QSettings>

formInicio::formInicio(QSqlDatabase db, QWidget *parent):
    QMainWindow(parent), ui(new Ui::formInicio), m_db(db){
    ui->setupUi(this);
    connect(ui->buttonSwitchUsuario, &QPushButton::clicked, this, &formInicio::abrirTelaUsuario);
    connect(ui->buttonExit, &QPushButton::clicked, this, &QApplication::quit);

    // Chama a função para personalizar a UI
    atualizarBoasVindas();
    carregarUsuarioInicial();

}

formInicio::~formInicio() {
    delete ui;
}

void formInicio::carregarUsuarioInicial()
{
    qDebug() << "formInicio: Verificando estado dos usuários...";
    QSettings settings("BrunoApps", "MeuCentavoApp");
    UsuarioDAO dao(m_db);

    // 1. Primeiro, verificamos se AINDA existe algum usuário.
    if (dao.existemUsuarios()) {
        // 2. SE SIM, comportamento normal: carrega o último/preferencial
        qDebug() << "Ainda existem usuários. Carregando usuário no botão.";
        if (auto usuarioOpt = dao.obterUsuarioPorId(settings.value("ultimoUsuarioId", -1).toInt())) { // Exemplo com QSettings
            ui->buttonAppAcess->setText(usuarioOpt->nomeUsuario);
        } else if (auto ultimoUsuarioOpt = dao.obterUltimoUsuario()) {
            ui->buttonAppAcess->setText(ultimoUsuarioOpt->nomeUsuario);
        }
    } else {
        // 3. SE NÃO, aqui está a nova lógica!
        qDebug() << "Nenhum usuário restante! Trocando para a tela de boas-vindas.";

        // Cria e mostra a tela de boas-vindas
        formBoasVindas *janelaBoasVindas = new formBoasVindas(m_db, nullptr);
        janelaBoasVindas->setAttribute(Qt::WA_DeleteOnClose);
        janelaBoasVindas->show();

        // E fecha a si mesma (a formInicio), completando a transição.
        this->close();
    }
}


void formInicio::atualizarUsuarioNoBotao(const Usuario& usuario)
{
    qDebug() << "formInicio: Recebeu o usuário selecionado:" << usuario.nomeUsuario;
     ui->buttonAppAcess->setText(usuario.nomeUsuario);

    // --- SALVANDO A ESCOLHA ---
    // Criamos um objeto QSettings, definindo o nome da sua organização e da aplicação
    QSettings settings("BrunoApps", "MeuCentavoApp");
    // Salvamos o ID do usuário com a chave "ultimoUsuarioId"
    settings.setValue("ultimoUsuarioId", usuario.id);
    qDebug() << "ID" << usuario.id << "salvo como último usuário.";

}


void formInicio::abrirTelaUsuario() {

    if (!usuarioWindow) {
        usuarioWindow = new formUsuario(m_db, nullptr);

        connect(usuarioWindow, &formUsuario::usuarioAtual,
                this, &formInicio::atualizarUsuarioNoBotao);

        connect(usuarioWindow, &formUsuario::usuarioFechado, [this]() {
            this->show();
            this->carregarUsuarioInicial();
            this->usuarioWindow = nullptr;
        });
    }

    this->hide();
    usuarioWindow->show();
}

void formInicio::atualizarBoasVindas()
{
    // Supondo que você tenha um QLabel no seu formInicio.ui chamado 'labelBoasVindas'
    // Você pode usar HTML simples para formatar o texto.
    QString texto = QString("Olá, <b>%1</b>!").arg(m_usuarioAtual.nomeUsuario);
    ui->buttonAppAcess->setText(texto);
}

