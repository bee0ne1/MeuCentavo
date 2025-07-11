#include "formAdicionarLancamento.h"
#include "ui_formAdicionarLancamento.h"
#include "DataAccess/LancamentoDAO.h"
#include "Modelo/Lancamento.h"
#include <QMessageBox>
#include <QDate>

formAdicionarLancamento::formAdicionarLancamento(int usuarioId, QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formAdicionarLancamento),
    m_db(db),
    m_usuarioId(usuarioId)
{
    ui->setupUi(this);
    setWindowTitle("Adicionar Lançamento");

    // Configurações iniciais dos campos
    ui->comboBoxTipo->addItems({"Despesa", "Receita"});
    ui->dateEditData->setDate(QDate::currentDate());
    ui->spinBoxValor->setMinimum(0.01);
    ui->spinBoxValor->setMaximum(999999.99);

    // Conexões dos botões
    connect(ui->buttonCancelar, &QPushButton::clicked, this, &QDialog::reject); // 'reject' fecha o diálogo
}

formAdicionarLancamento::~formAdicionarLancamento()
{
    delete ui;
}

void formAdicionarLancamento::on_buttonSalvar_clicked()
{
    // 1. Validação simples
    if (ui->lineEditDescricao->text().isEmpty()) {
        QMessageBox::warning(this, "Campo Obrigatório", "A descrição não pode estar vazia.");
        return;
    }

    // 2. Coleta dos dados da interface
    Lancamento novoLancamento;
    novoLancamento.descricao = ui->lineEditDescricao->text();
    novoLancamento.valor = ui->spinBoxValor->value();
    novoLancamento.data_lancamento = ui->dateEditData->date();
    novoLancamento.tipo = ui->comboBoxTipo->currentText();
    novoLancamento.id_usuario = m_usuarioId; // Usa o ID recebido no construtor

    // 3. Salva no banco de dados através do DAO
    LancamentoDAO dao(m_db);
    if (dao.adicionarLancamento(novoLancamento)) {
        QMessageBox::information(this, "Sucesso", "Lançamento adicionado com sucesso!");
        emit lancamentoSalvo(); // Emite o sinal para avisar outras janelas
        this->accept(); // 'accept' fecha o diálogo com sucesso
    } else {
        QMessageBox::critical(this, "Erro de Banco de Dados", "Não foi possível salvar o lançamento.");
    }
}
