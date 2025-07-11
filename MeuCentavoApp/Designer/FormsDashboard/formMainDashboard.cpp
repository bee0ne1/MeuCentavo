#include "formMainDashboard.h"
#include "ui_formMainDashboard.h"

// Incluímos os cabeçalhos das "páginas" que vamos adicionar ao QStackedWidget.
#include "DashboardPages/pageHome.h"
#include "DashboardPages/pageRelatorios.h"
#include "DashboardPages/pageLancamentos.h"

#include <QDebug>

formMainDashboard::formMainDashboard(const Usuario& usuario, QSqlDatabase db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::formMainDashboard),
    m_db(db),
    m_usuarioAtual(usuario)
{
    // Configura a interface criada no Qt Designer. Essencial!
    ui->setupUi(this);

    // Define um título para a janela.
    setWindowTitle("Meu Centavo - Dashboard");
    
    // Chama a função para configurar as páginas e o QStackedWidget.
    setupPaginas();
}

formMainDashboard::~formMainDashboard()
{
    // Libera a memória alocada para a interface.
    delete ui;
}

void formMainDashboard::setupPaginas()
{

    // --- LIMPEZA DO STACKED WIDGET (MÉTODO RECOMENDADO) ---
    while (ui->stackedWidgetConteudo->count() > 0)
    {
        QWidget* page = ui->stackedWidgetConteudo->widget(0);
        ui->stackedWidgetConteudo->removeWidget(page);
        // Usar deleteLater() é mais seguro que 'delete' para objetos Qt
        page->deleteLater();
    }

    // 1. Cria uma instância de cada uma das suas páginas.
    pageHome *paginaHome = new pageHome(m_usuarioAtual, m_db, this);
    pageRelatorios *paginaRelatorios = new pageRelatorios(m_usuarioAtual, m_db, this);
    pageLancamentos *paginaLancamentos = new pageLancamentos(m_usuarioAtual,m_db,this);


    // 2. Adiciona as páginas ao seu QStackedWidget. A ORDEM IMPORTA!
    // Supondo que o objectName no .ui seja 'stackedWidgetConteudo'.
    ui->stackedWidgetConteudo->addWidget(paginaHome);
    ui->stackedWidgetConteudo->addWidget(paginaLancamentos);
    ui->stackedWidgetConteudo->addWidget(paginaRelatorios);
    // 3. Define qual página deve aparecer primeiro.
    ui->stackedWidgetConteudo->setCurrentIndex(0); // Mostra a página Home por padrão.
    qDebug() << "Dashboard configurada e página Home exibida.";
}


// --- Implementação dos Slots de Navegação ---

void formMainDashboard::on_buttonHome_clicked()
{
    // Diz ao QStackedWidget para mostrar a página no índice 0.
    ui->stackedWidgetConteudo->setCurrentIndex(0);
}

void formMainDashboard::on_buttonLancamentos_clicked()
{
    ui->stackedWidgetConteudo->setCurrentIndex(1);
}

void formMainDashboard::on_buttonRelatorios_clicked()
{
    // Mostra a página no índice 1.
    ui->stackedWidgetConteudo->setCurrentIndex(2);
}


void formMainDashboard::on_buttonConfiguracoes_clicked()
{
    // Supondo que a página de configurações seja a quarta (índice 3)
    // ui->stackedWidgetConteudo->setCurrentIndex(3);
    qDebug() << "Botão Configurações clicado! (Página ainda não adicionada)";
}