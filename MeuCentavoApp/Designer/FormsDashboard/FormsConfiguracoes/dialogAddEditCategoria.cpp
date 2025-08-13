#include "dialogAddEditCategoria.h"
#include "ui_dialogAddEditCategoria.h"

dialogAddEditCategoria::dialogAddEditCategoria(const QString& tipoPerfil, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAddEditCategoria)
{
    ui->setupUi(this);
    m_idCategoria = -1; // Inicia em modo "Adicionar"
    m_tipoPerfil = tipoPerfil;

    // Controla a visibilidade do campo de classificação contábil
    bool isPerfilPJ = (tipoPerfil == "PJ");
    ui->widgetClassificacao->setVisible(isPerfilPJ);

    if (isPerfilPJ) {
        // Se for um perfil de empresa, popula o ComboBox com as classificações para um DRE
        ui->comboClassificacao->addItem("Receita Bruta", "Receita Bruta");
        ui->comboClassificacao->addItem("Dedução da Receita", "Dedução da Receita");
        ui->comboClassificacao->addItem("Custo do Serviço/Produto", "Custo do Serviço/Produto");
        ui->comboClassificacao->addItem("Despesa Operacional", "Despesa Operacional");
        ui->comboClassificacao->addItem("Receita Financeira", "Receita Financeira");
        ui->comboClassificacao->addItem("Despesa Financeira", "Despesa Financeira");
        ui->comboClassificacao->addItem("Imposto sobre o Lucro", "Imposto sobre o Lucro");
        ui->comboClassificacao->addItem("Outras Receitas", "Outras Receitas");
        ui->comboClassificacao->addItem("Outras Despesas", "Outras Despesas");
    }

    // Conecta os botões "OK" e "Cancelar" às ações padrão do diálogo
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

dialogAddEditCategoria::~dialogAddEditCategoria()
{
    delete ui;
}

// Função para preencher os dados no modo de edição
void dialogAddEditCategoria::setDados(const Categoria& categoria)
{
    m_idCategoria = categoria.id;
    ui->lineEditNome->setText(categoria.nome);

    // Se o campo de classificação estiver visível (modo PJ), seleciona o item correto
    if (ui->widgetClassificacao->isVisible()) {
        int index = ui->comboClassificacao->findData(categoria.classificacao_contabil);
        if (index != -1) {
            ui->comboClassificacao->setCurrentIndex(index);
        }
    }
}

// Função para obter os dados preenchidos pelo usuário
Categoria dialogAddEditCategoria::getDados() const
{
    Categoria cat;
    cat.id = m_idCategoria;
    cat.nome = ui->lineEditNome->text();

    if (m_tipoPerfil == "PJ") {
        cat.classificacao_contabil = ui->comboClassificacao->currentData().toString();
    }

    return cat;
}