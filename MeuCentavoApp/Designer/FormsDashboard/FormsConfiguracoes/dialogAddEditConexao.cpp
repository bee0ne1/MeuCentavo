#include "dialogAddEditConexao.h"
#include "ui_dialogAddEditConexao.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h"
#include <QWebEngineView>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QUrlQuery>

dialogAddEditConexao::dialogAddEditConexao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAddEditConexao)
{
    ui->setupUi(this);
    setWindowTitle("Conectar Nova Conta Bancária");
    setMinimumSize(450, 600);

    // Se você promoveu o widget no Designer, use ui->webView diretamente.
    // Se não, criamos um aqui:
    m_webView = ui->webView; // Assumindo que o objectName é 'webView'
    if (!m_webView) { // Fallback se não foi promovido
        m_webView = new QWebEngineView(this);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(m_webView);
        setLayout(layout);
    }

    m_dao = new LancamentoDAO(this);

    connect(m_dao, &LancamentoDAO::connectTokenRecebido, this, &dialogAddEditConexao::onConnectTokenRecebido);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &dialogAddEditConexao::onErro);
    connect(m_webView, &QWebEngineView::urlChanged, this, &dialogAddEditConexao::onUrlChanged);

    // Inicia o processo imediatamente ao abrir o diálogo
    m_webView->setHtml("<html><body><h1>Carregando ambiente seguro...</h1></body></html>");
    QString token = SessionManager::instance().getToken();
    m_dao->obterConnectToken(token);
}

dialogAddEditConexao::~dialogAddEditConexao()
{
    delete ui;
}

void dialogAddEditConexao::onConnectTokenRecebido(const QString& connectToken)
{
    if (connectToken.isEmpty()) {
        onErro("O servidor não retornou um token de conexão válido.");
        return;
    }
    
    // Monta a URL do widget da Pluggy com o token recebido
    QUrl url("https://connect.pluggy.ai/");
    QUrlQuery query;
    query.addQueryItem("connect_token", connectToken);
    url.setQuery(query);

    // Carrega o widget no nosso navegador
    m_webView->load(url);
}

void dialogAddEditConexao::onUrlChanged(const QUrl& url)
{
    // A Pluggy redireciona para uma URL com este parâmetro quando o processo é bem-sucedido
    if (url.toString().contains("event_name=finished")) {
        emit conexaoSucedida();
        QMessageBox::information(this, "Sucesso", "Conta conectada com sucesso! Os dados podem levar alguns minutos para serem sincronizados.");
        this->accept(); // Fecha o diálogo com status de sucesso
    }
}

void dialogAddEditConexao::onErro(const QString& motivo)
{
    QMessageBox::critical(this, "Erro de Conexão", motivo);
    this->reject(); // Fecha o diálogo com status de erro
}