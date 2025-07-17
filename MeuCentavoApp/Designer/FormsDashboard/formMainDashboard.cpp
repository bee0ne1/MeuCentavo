#include "formMainDashboard.h"
#include "ui_formMainDashboard.h"
#include "Gerenciamento/SessionManager.h" // Inclui nosso novo "cofre"
#include "Designer/FormsLogin/formUsuario.h"
#include "DashboardPages/pageHome.h"
#include "DashboardPages/pageLancamentos.h"
//#include "DashboardPages/pageRelatorios.h"

#include <QDebug>
#include <QMessageBox>

formMainDashboard::formMainDashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::formMainDashboard)
{
    ui->setupUi(this);
    m_formUsuario = nullptr;
    setWindowTitle("Meu Centavo - Dashboard");
    setupPaginas(); // Chama a função para configurar as páginas
}

formMainDashboard::~formMainDashboard()
{
    delete ui;
}

void formMainDashboard::setupPaginas()
{
    // Limpa o stacked widget de páginas padrão do Designer
    while (ui->stackedWidgetConteudo->count() > 0) {
        QWidget* page = ui->stackedWidgetConteudo->widget(0);
        ui->stackedWidgetConteudo->removeWidget(page);
        page->deleteLater();
    }

    // Cria as instâncias das páginas. Note que os construtores delas também
    // serão simplificados, pois elas mesmas podem acessar o SessionManager.
    m_pageHome = new pageHome(this);
    m_pageLancamentos = new pageLancamentos(this);
    //m_pageRelatorios = new pageRelatorios(this);

    // Adiciona as páginas ao "baralho"
    ui->stackedWidgetConteudo->addWidget(m_pageHome);          // Índice 0
    ui->stackedWidgetConteudo->addWidget(m_pageLancamentos);    // Índice 1
    //ui->stackedWidgetConteudo->addWidget(m_pageRelatorios);     // Índice 2

    // Define a página inicial
    ui->stackedWidgetConteudo->setCurrentIndex(0);
    qDebug() << "Dashboard configurada e página Home exibida.";
}

// Os slots de navegação continuam funcionando da mesma forma
void formMainDashboard::on_buttonHome_clicked()
{
    ui->stackedWidgetConteudo->setCurrentIndex(0);
}

void formMainDashboard::on_buttonLancamentos_clicked()
{
    ui->stackedWidgetConteudo->setCurrentIndex(1);
}

void formMainDashboard::on_buttonRelatorios_clicked()
{
    ui->stackedWidgetConteudo->setCurrentIndex(2);
}

void formMainDashboard::on_buttonConfiguracoes_clicked()
{
    qDebug() << "Botão Configurações clicado!";
}

void formMainDashboard::on_buttonSwitchUsuario_clicked()
{
    qDebug() << "Dashboard: Botão 'Trocar Usuário' clicado.";

    // 1. Lógica para não abrir múltiplas janelas ao mesmo tempo
    // Se a janela já existe e está visível, apenas a traga para frente.
    if (m_formUsuario) {
        m_formUsuario->activateWindow();
        return;
    }

    // 2. Pega o token da sessão atual. Como estamos logados, ele deve existir.
    QString token = SessionManager::instance().getToken();
    if (token.isEmpty()) {
        QMessageBox::critical(this, "Erro de Sessão", "Sua sessão é inválida. Por favor, reinicie o aplicativo.");
        return;
    }
    qDebug() << "Token recuperado para abrir a tela de usuários:" << token;

    // 3. Cria a janela de seleção, passando o token válido.
    // Usamos 'nullptr' como pai para garantir que ela seja uma janela independente.
    m_formUsuario = new formUsuario(token, nullptr);
    m_formUsuario->setWindowModality(Qt::ApplicationModal);

    // 4. Conecta o sinal de destruição da janela para limparmos nosso ponteiro.
    // Isso nos permite clicar no botão e abrir a janela novamente no futuro.
    connect(m_formUsuario, &QObject::destroyed, this, [this]() {
        qDebug() << "Janela formUsuario foi destruída. Limpando ponteiro m_formUsuario.";
        this->m_formUsuario = nullptr;
    });

    // 5. Mostra a janela de gerenciamento.
    // A dashboard (this) continua visível no fundo.
    m_formUsuario->show();
}