#include "formAdicionarLancamento.h"
#include "ui_formAdicionarLancamento.h"
#include "DataAccess/LancamentoDAO.h"
#include "Modelo/Lancamento.h"
#include "Designer/Gerenciamento/SessionManager.h" // Inclui nosso "cofre" de sessão
#include <QMessageBox>
#include <QDate>
#include <QDebug>

formAdicionarLancamento::formAdicionarLancamento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formAdicionarLancamento)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Adicionar Novo Lançamento");

    // Configurações iniciais dos campos (continua igual)
    ui->comboBoxTipo->addItems({"Despesa", "Receita"});
    ui->dateEditData->setDate(QDate::currentDate());
    ui->spinBoxValor->setMinimum(0.01);
    ui->spinBoxValor->setMaximum(9999999.99);

    // Conectamos o botão Salvar ao nosso novo slot
    connect(ui->buttonSalvar, &QPushButton::clicked, this, &formAdicionarLancamento::salvarLancamento);
    connect(ui->buttonCancelar, &QPushButton::clicked, this, &QDialog::reject);
}

formAdicionarLancamento::~formAdicionarLancamento()
{
    delete ui;
}

void formAdicionarLancamento::salvarLancamento()
{
    // 1. Validação da UI
    if (ui->lineEditDescricao->text().isEmpty()) {
        QMessageBox::warning(this, "Campo Obrigatório", "A descrição não pode estar vazia.");
        return;
    }

    // Desabilita o botão para evitar múltiplos cliques
    ui->buttonSalvar->setEnabled(false);
    ui->buttonSalvar->setText("Salvando...");

    // 2. Coleta dos dados da interface
    Lancamento novoLancamento;
    novoLancamento.descricao = ui->lineEditDescricao->text();
    novoLancamento.valor = ui->spinBoxValor->value();
    novoLancamento.data_lancamento = ui->dateEditData->date();
    novoLancamento.tipo = ui->comboBoxTipo->currentText();
    // O ID do usuário e da conta/categoria serão tratados pelo backend ou DAO

    // 3. Pega o token de autenticação do nosso "cofre"
    QString token = SessionManager::instance().getToken();

    // 4. Inicia a requisição de rede através do DAO
    LancamentoDAO *dao = new LancamentoDAO(this);

    // Conecta os sinais do DAO aos nossos slots de resposta
    connect(dao, &LancamentoDAO::lancamentoAdicionado, this, &formAdicionarLancamento::onLancamentoAdicionado);
    connect(dao, &LancamentoDAO::erroOcorrido, this, &formAdicionarLancamento::onErroDeRede);

    dao->adicionarLancamento(novoLancamento, token);
}

void formAdicionarLancamento::onLancamentoAdicionado()
{
    // O DAO nos avisou que a API retornou sucesso!
    qDebug() << "Lançamento adicionado com sucesso, fechando diálogo.";

    // Avisa a página anterior (ex: pageLancamentos) que ela pode se atualizar
    emit lancamentoSalvo();

    // Fecha o diálogo com o status de "Aceito"
    this->accept();
}

void formAdicionarLancamento::onErroDeRede(const QString& motivo)
{
    // O DAO nos avisou que a API retornou um erro
    QMessageBox::critical(this, "Erro de Rede", motivo);

    // Reabilita o botão para o usuário poder tentar novamente
    ui->buttonSalvar->setEnabled(true);
    ui->buttonSalvar->setText("Salvar");
}