#include "formInicio.h"
#include "ui_formInicio.h"
#include "FormsLogin/formUsuario.h"
#include "FormsLogin/formBoasVindas.h"
#include "FormsLogin/formLoginSenha.h"
#include "FormsDashboard/formMainDashboard.h"
#include <QDebug>
#include "DataAccess//UsuarioDAO.h"
#include <QSettings>
#include <QMessageBox>

formInicio::formInicio(QSqlDatabase db, QWidget *parent):
    QMainWindow(parent), ui(new Ui::formInicio), m_db(db){
    ui->setupUi(this);
    connect(ui->buttonSwitchUsuario, &QPushButton::clicked, this, &formInicio::abrirTelaUsuario);
    connect(ui->buttonExit, &QPushButton::clicked, this, &QApplication::quit);
    connect(ui->buttonAppAcess, &QPushButton::clicked, this, &formInicio::abrirTelaLogin);

    carregarUsuarioInicial();

}

formInicio::~formInicio() {
    delete ui;
}

void formInicio::carregarUsuarioInicial()
{
    qDebug() << "formInicio: Verificando estado dos usuários...";
    // Limpa o usuário atual antes de tentar carregar um novo.
    m_usuarioAtual.reset();

    UsuarioDAO dao(m_db);

    if (dao.existemUsuarios()) {
        QSettings settings("BrunoApps", "MeuCentavoApp");
        int ultimoId = settings.value("ultimoUsuarioId", -1).toInt();

        // Variável local para guardar o usuário que decidirmos exibir.
        std::optional<Usuario> usuarioParaExibir;

        if (ultimoId != -1) {
            // Tenta buscar o usuário salvo nas configurações.
            usuarioParaExibir = dao.obterUsuarioPorId(ultimoId);
        }

        // Se não encontrou um usuário pelo ID salvo (talvez ele foi deletado),
        // busca o último usuário do banco como um fallback.
        if (!usuarioParaExibir) {
            usuarioParaExibir = dao.obterUltimoUsuario();
        }

        // --- AQUI ESTÁ A LÓGICA ADICIONADA ---
        if (usuarioParaExibir) {
            // 1. Guarda o objeto de usuário completo na variável membro.
            m_usuarioAtual = *usuarioParaExibir; // O '*' extrai o valor do optional.

            // 2. Atualiza o texto do botão.
            ui->buttonAppAcess->setText(m_usuarioAtual->nomeUsuario);
            ui->buttonAppAcess->setEnabled(true);
            qDebug() << "Usuário '" << m_usuarioAtual->nomeUsuario << "' carregado na tela inicial.";
        }
        // --- FIM DA LÓGICA ---

    } else {
        // Se não existe nenhum usuário, desabilita o botão principal.
        qDebug() << "Nenhum usuário no banco. Trocando para a tela de boas-vindas.";
        ui->buttonAppAcess->setText("Cadastrar Primeiro Usuário");
        ui->buttonAppAcess->setEnabled(false); // Opcional, mas boa UX

        // Cria e mostra a tela de boas-vindas.
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

void formInicio::abrirTelaLogin()
{
    // Primeiro, precisamos saber qual usuário está selecionado.
    // Vamos assumir que você tem uma variável 'm_usuarioAtual' na formInicio
    // que é atualizada pela função carregarUsuarioInicial().

    if (!m_usuarioAtual) { // Se por algum motivo nenhum usuário foi carregado
        QMessageBox::information(this, "Nenhum Usuário", "Por favor, selecione ou cadastre um usuário.");
        return;
    }

    // Cria o diálogo de senha para o usuário atual
    formLoginSenha dialogoSenha(*m_usuarioAtual, m_db, this);

    // Executa o diálogo de forma modal (bloqueia a janela de trás)
    // e verifica se o usuário clicou em "Entrar" (Accepted) ou "Cancelar" (Rejected)
    if (dialogoSenha.exec() == QDialog::Accepted) {
        // SENHA CORRETA!
        qDebug() << "Autenticação bem-sucedida para" << m_usuarioAtual->nomeUsuario;

        // Agora sim, abre a janela principal do aplicativo
        this->hide();
        formMainDashboard *dashboard = new formMainDashboard(*m_usuarioAtual, m_db);
        dashboard->showMaximized();
        this->close(); // Fecha a tela de início
    } else {
        // SENHA INCORRETA OU CANCELADO
        qDebug() << "Autenticação cancelada ou falhou.";
        // Não faz nada, o usuário continua na tela formInicio.
    }
}

