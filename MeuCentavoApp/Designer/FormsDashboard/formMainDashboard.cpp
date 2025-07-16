#include "formMainDashboard.h"
#include "ui_formMainDashboard.h"
#include "Gerenciamento/SessionManager.h" // Inclui nosso novo "cofre"

// Incluímos os cabeçalhos das páginas
#include "DashboardPages/pageHome.h"
#include "DashboardPages/pageLancamentos.h"
//#include "DashboardPages/pageRelatorios.h"

#include <QDebug>

formMainDashboard::formMainDashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::formMainDashboard)
{
    ui->setupUi(this);
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