#include "formMain.h"
#include "ui_formMain.h"
#include "Forms/formUsuario.h"  // Inclui as definições das janelas que vai abrir
#include <QDebug>
#include "DataAccess//UsuarioDAO.h" // Precisa do DAO para buscar
#include <QSettings>

formMain::formMain(QSqlDatabase db, QWidget *parent):
    QMainWindow(parent), ui(new Ui::formMain), m_db(db){
    ui->setupUi(this);
    connect(ui->buttonSwitchUsuario, &QPushButton::clicked, this, &formMain::abrirTelaUsuario);
    connect(ui->buttonExit, &QPushButton::clicked, this, &QApplication::quit);

    // Chama a função para personalizar a UI
    atualizarBoasVindas();
    carregarUsuarioInicial();

}

formMain::~formMain() {
    delete ui;
}

void formMain::carregarUsuarioInicial()
{
    qDebug() << "formMain: Carregando usuário inicial...";
    QSettings settings("BrunoApps", "MeuCentavoApp");
    UsuarioDAO dao(m_db);

    // 1. Tenta ler o ID salvo. Se não houver, usa -1 como padrão.
    int ultimoId = settings.value("ultimoUsuarioId", -1).toInt();

    std::optional<Usuario> usuarioParaExibir;

    if (ultimoId != -1) {
        // 2. Se encontrou um ID salvo, tenta buscar esse usuário específico.
        qDebug() << "Encontrado ID salvo:" << ultimoId << ". Buscando usuário...";
        usuarioParaExibir = dao.obterUsuarioPorId(ultimoId);
    }

    // 3. Se não havia ID salvo, OU se o usuário salvo foi deletado,
    //    buscamos o último usuário cadastrado como um fallback.
    if (!usuarioParaExibir) {
        qDebug() << "Nenhum usuário salvo/válido encontrado. Buscando o último do banco...";
        usuarioParaExibir = dao.obterUltimoUsuario();
    }

    // 4. Atualiza o botão
    if (usuarioParaExibir) {
        ui->buttonAppAcess->setText(usuarioParaExibir->nomeUsuario);
    } else {
        ui->buttonAppAcess->setText("Cadastrar Usuário");
        ui->buttonAppAcess->setEnabled(false);
    }
}


void formMain::atualizarUsuarioNoBotao(const Usuario& usuario)
{
    qDebug() << "formMain: Recebeu o usuário selecionado:" << usuario.nomeUsuario;
     ui->buttonAppAcess->setText(usuario.nomeUsuario);

    // --- SALVANDO A ESCOLHA ---
    // Criamos um objeto QSettings, definindo o nome da sua organização e da aplicação
    QSettings settings("BrunoApps", "MeuCentavoApp");
    // Salvamos o ID do usuário com a chave "ultimoUsuarioId"
    settings.setValue("ultimoUsuarioId", usuario.id);
    qDebug() << "ID" << usuario.id << "salvo como último usuário.";

}


void formMain::abrirTelaUsuario() {

    if (!usuarioWindow) {
        usuarioWindow = new formUsuario(m_db, nullptr);

        connect(usuarioWindow, &formUsuario::usuarioAtual,
                this, &formMain::atualizarUsuarioNoBotao);

        connect(usuarioWindow, &formUsuario::usuarioFechado, [this]() {
            // 1. Reexibe a janela principal
            this->show();
            // 2. Limpa o ponteiro para que a janela possa ser recriada na próxima vez
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

