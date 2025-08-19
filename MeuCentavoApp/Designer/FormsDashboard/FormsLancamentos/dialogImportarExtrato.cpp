#include "../FormsLancamentos/dialogImportarExtrato.h"
#include "ui_dialogImportarExtrato.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h"
#include <QFileDialog>

dialogImportarExtrato::dialogImportarExtrato(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogImportarExtrato)
{
    ui->setupUi(this);
    setWindowTitle("Iniciar Importação de Extrato");

    m_dao = new LancamentoDAO(this);

    // Conecta o botão "OK" (Importar) ao slot que fecha o diálogo com sucesso.
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    // Conecta o botão "Cancelar" ao slot que fecha o diálogo como cancelado.
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    connect(m_dao, &LancamentoDAO::contasRecebidas, this, &dialogImportarExtrato::onContasRecebidas);

    // Carrega as contas do usuário para preencher o ComboBox
    QString token = SessionManager::instance().getToken();
    m_dao->obterTodasContas(token);
}

dialogImportarExtrato::~dialogImportarExtrato()
{
    delete ui;
}

QString dialogImportarExtrato::caminhoArquivoSelecionado() const
{
    return m_caminhoArquivo;
}

int dialogImportarExtrato::idContaSelecionada() const
{
    return ui->comboBoxConta->currentData().toInt();
}

void dialogImportarExtrato::on_buttonSelecionarArquivo_clicked()
{
    // O filtro agora aceita tanto CSV quanto PDF
    QString filtroArquivos = "Extratos Bancários (*.csv *.pdf)";
    m_caminhoArquivo = QFileDialog::getOpenFileName(this, "Selecionar Extrato", QDir::homePath(), filtroArquivos);

    if (!m_caminhoArquivo.isEmpty()) {
        ui->lineEditCaminhoArquivo->setText(m_caminhoArquivo);
    }
}

void dialogImportarExtrato::onContasRecebidas(const QVector<Conta>& contas)
{
    ui->comboBoxConta->clear();
    for (const auto& conta : contas) {
        ui->comboBoxConta->addItem(conta.nome, conta.id);
    }
}

