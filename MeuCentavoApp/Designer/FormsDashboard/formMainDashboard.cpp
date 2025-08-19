#include "formMainDashboard.h"
#include "ui_formMainDashboard.h"
#include "Gerenciamento/SessionManager.h" // Inclui nosso novo "cofre"
#include "Designer/FormsUsuarios/formUsuario.h"
#include "DashboardPages/pageHome.h"
#include "DashboardPages/pageLancamentos.h"
#include "DashboardPages/pageConfig.h"
#include "DashboardPages/pageRelatorios.h"
#include "DashboardPages/pageDividas.h"
#include "DataAccess/UsuarioDAO.h"
#include <QDebug>
#include <QMessageBox>

formMainDashboard::formMainDashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::formMainDashboard)
{
    ui->setupUi(this);
    setWindowTitle("Meu Centavo - Dashboard");
    m_formUsuario = nullptr;
    m_usuarioDAO = new UsuarioDAO(this); // Crie a instância do DAO
    setupPaginas();

    // --- CONEXÕES PARA GESTÃO DE PERFIS ---
    connect(m_usuarioDAO, &UsuarioDAO::perfisRecebidos, this, &formMainDashboard::onPerfisRecebidos);
    connect(m_usuarioDAO, &UsuarioDAO::novoTokenRecebido, this, &formMainDashboard::onNovoTokenRecebido);
    connect(ui->comboPerfisAtivos, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &formMainDashboard::onPerfilAlterado);
    connect(m_pageConfig, &pageConfig::listaDePerfisAtualizada, this, &formMainDashboard::onListaDePerfisModificada);

    carregarPerfisDoUsuario();

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
    m_pageRelatorios = new pageRelatorios(this);
    m_pageMetas = new pageMetas(this);
    m_pageInvestimentos = new pageInvestimentos(this);
    m_pageDividas = new pageDividas(this);
    m_pageConfig = new pageConfig(this);

    // Adiciona as páginas ao "baralho"
    ui->stackedWidgetConteudo->addWidget(m_pageHome);          // Índice 0
    ui->stackedWidgetConteudo->addWidget(m_pageLancamentos);    // Índice 1
    ui->stackedWidgetConteudo->addWidget(m_pageRelatorios);     // Índice 2
    ui->stackedWidgetConteudo->addWidget(m_pageMetas);          //indice 3
    ui->stackedWidgetConteudo->addWidget(m_pageInvestimentos); //indice 4
    ui->stackedWidgetConteudo->addWidget(m_pageDividas); //indice 5
    ui->stackedWidgetConteudo->addWidget(m_pageConfig);         // indice 6


    connect(m_pageLancamentos, &pageLancamentos::dadosAtualizados, m_pageHome, &pageHome::atualizarDados);
    connect(m_pageLancamentos, &pageLancamentos::dadosAtualizados, m_pageRelatorios, &pageRelatorios::carregarDados);

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

void formMainDashboard::on_buttonMetas_clicked()
{
    // Chama a função pública para recarregar os dados da página de metas.
    m_pageMetas->carregarMetas();

    ui->stackedWidgetConteudo->setCurrentIndex(3);
}

void formMainDashboard::on_buttonInvestimentos_clicked()
{
    ui->stackedWidgetConteudo->setCurrentIndex(4);
}

void formMainDashboard::on_buttonDividas_clicked()
{
    // Pede para a página carregar/atualizar seus dados
    m_pageDividas->carregarDados();
    // Muda para o índice correto da página de dívidas
    ui->stackedWidgetConteudo->setCurrentIndex(5);
}


void formMainDashboard::on_buttonConfiguracoes_clicked()
{
    ui->stackedWidgetConteudo->setCurrentIndex(6);
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

void formMainDashboard::recarregarTodasAsPaginas()
{
    qDebug() << "Dashboard: Recarregando dados de todas as páginas...";
    m_pageHome->atualizarDados();
    m_pageLancamentos->carregarTabela();
    m_pageRelatorios->carregarDados();
    m_pageMetas->carregarMetas();
    m_pageInvestimentos->carregarAtivos();
    m_pageDividas->carregarDados();
}

void formMainDashboard::onPerfisRecebidos(const QVector<Perfil>& perfis)
{
    int perfilAtivoId = SessionManager::instance().getPerfilId();
    bool perfilAtivoAindaExiste = false;
    int perfilPessoalId = -1;

    // 1. Itera sobre a nova lista de perfis para verificar duas coisas:
    //    - Se o perfil que ESTÁ ATIVO na sessão ainda existe.
    //    - Qual é o ID do perfil de Pessoa Física (nosso porto seguro).
    for (const auto& perfil : perfis) {
        if (perfil.id_perfil == perfilAtivoId) {
            perfilAtivoAindaExiste = true;
        }
        if (perfil.tipo_perfil == "PF") {
            perfilPessoalId = perfil.id_perfil;
        }
    }

    // 2. LÓGICA DE CORREÇÃO DE ESTADO
    // Se o perfil ativo foi excluído E nós encontramos um perfil PF para onde voltar...
    if (!perfilAtivoAindaExiste && perfilPessoalId != -1) {
        qDebug() << "Dashboard: Perfil ativo foi excluído! Forçando troca para o perfil Pessoal (ID:" << perfilPessoalId << ")";
        // Dispara a troca de perfil. O resto do fluxo (onNovoTokenRecebido -> recarregarTudo)
        // cuidará da atualização de dados.
        onPerfilAlterado(ui->comboPerfisAtivos->findData(perfilPessoalId));
        // A função para aqui, pois a troca de perfil irá recarregar tudo.
        return;
    }

    // 3. Se o estado estiver normal, apenas atualiza o ComboBox
    qDebug() << "Dashboard: Atualizando o ComboBox de perfis.";
    ui->comboPerfisAtivos->blockSignals(true);
    ui->comboPerfisAtivos->clear();
    int indexParaSelecionar = 0;
    for (int i = 0; i < perfis.size(); ++i) {
        const auto& perfil = perfis[i];
        QString textoItem = QString("%1 (%2)").arg(perfil.nome_perfil).arg(perfil.tipo_perfil);
        ui->comboPerfisAtivos->addItem(textoItem, perfil.id_perfil);
        if (perfil.id_perfil == perfilAtivoId) {
            indexParaSelecionar = i;
        }
    }
    ui->comboPerfisAtivos->setCurrentIndex(indexParaSelecionar);
    ui->comboPerfisAtivos->blockSignals(false);
}


void formMainDashboard::onPerfilAlterado(int index)
{
    if (index < 0) return;
    int idPerfil = ui->comboPerfisAtivos->itemData(index).toInt();

    // Evita recarregar se o usuário acidentalmente selecionar o mesmo perfil
    if (idPerfil == SessionManager::instance().getPerfilId()) return;

    // A única responsabilidade deste slot é iniciar a troca.
    // A resposta será tratada pelo slot 'onNovoTokenRecebido' que já está conectado.

    m_usuarioDAO->selecionarPerfil(idPerfil, SessionManager::instance().getToken());
}

void formMainDashboard::onNovoTokenRecebido(const QString& novoToken, const Usuario& usuario)
{
    qDebug() << "Dashboard: Novo token recebido. Atualizando sessão e recarregando páginas.";
    SessionManager::instance().salvarNovoToken(novoToken);

    // Atualiza o ComboBox para refletir a nova sessão
    carregarPerfisDoUsuario();

    // Recarrega os dados de todas as páginas
    recarregarTodasAsPaginas();
}

void formMainDashboard::onListaDePerfisModificada()
{
    qDebug() << "Dashboard: Detectou que a tela de perfis foi usada. Verificando estado da sessão...";
    // Apenas inicia o processo de recarregar a lista de perfis.
    // A lógica de correção acontecerá em onPerfisRecebidos.
    carregarPerfisDoUsuario();
}


void formMainDashboard::carregarPerfisDoUsuario()
{
    qDebug() << "Dashboard: Carregando perfis do usuário...";
    QString token = SessionManager::instance().getToken();
    if (!token.isEmpty()) {
        m_usuarioDAO->obterPerfis(token);
    }
}