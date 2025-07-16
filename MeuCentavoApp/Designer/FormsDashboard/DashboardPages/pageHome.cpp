#include "pageHome.h"
#include "ui_pageHome.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h" // Nosso "cofre" de sessão
#include <QHeaderView>
#include <QMessageBox>

pageHome::pageHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageHome)
{
    ui->setupUi(this);

    // Cria uma única instância do DAO para esta página
    m_dao = new LancamentoDAO(this);

    // Conecta os sinais de resultado do DAO aos nossos slots
    connect(m_dao, &LancamentoDAO::resumosRecebidos, this, &pageHome::onResumosRecebidos);
    connect(m_dao, &LancamentoDAO::lancamentosRecebidos, this, &pageHome::onLancamentosRecentesRecebidos);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &pageHome::onErroDeRede);

    // Configuração inicial da tabela
    ui->tabelaLancamentosRecentes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // Inicia a busca por dados assim que a página é criada
    atualizarDados();
}

pageHome::~pageHome()
{
    delete ui;
}

void pageHome::atualizarDados()
{
    // Pega o token e o ID do usuário do nosso "cofre" de sessão
    QString token = SessionManager::instance().getToken();
    int usuarioId = SessionManager::instance().getUsuarioId();

    if (!SessionManager::instance().estaLogado()) {
        qDebug() << "Erro: Tentando atualizar dados da home sem um usuário logado.";
        return;
    }

    // Inicia as requisições de rede. As respostas virão depois, nos slots.
    m_dao->obterResumosDoMes(token);
    m_dao->obterRecentes(token, usuarioId);
}

void pageHome::onResumosRecebidos(double receitas, double despesas)
{
    double saldo = receitas - despesas;

    ui->labelValorReceitas->setText(QString("R$ %1").arg(receitas, 0, 'f', 2));
    ui->labelValorDespesas->setText(QString("R$ %1").arg(despesas, 0, 'f', 2));
    ui->labelSaldoMes->setText(QString("R$ %1").arg(saldo, 0, 'f', 2));

    if (saldo < 0) {
        ui->labelSaldoMes->setStyleSheet("color: #e74c3c;");
    } else {
        ui->labelSaldoMes->setStyleSheet("color: #2ecc71;");
    }
}

void pageHome::onLancamentosRecentesRecebidos(const QVector<Lancamento>& lancamentos)
{
    ui->tabelaLancamentosRecentes->clearContents();
    ui->tabelaLancamentosRecentes->setRowCount(0);

    for (const auto& lancamento : lancamentos) {
        // ... sua lógica para popular a tabela continua a mesma ...
    }
}

void pageHome::onErroDeRede(const QString& erro)
{
    QMessageBox::critical(this, "Erro de Rede", "Não foi possível buscar os dados da dashboard:\n" + erro);
}