#include "pageRelatorios.h"
#include "ui_pageRelatorios.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h"

// Includes do Qt Charts
#include <QtCharts>
#include <QPushButton>
#include <QGraphicsLayout>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "Gerenciamento/SessionManager.h"

pageRelatorios::pageRelatorios(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageRelatorios)
{
    ui->setupUi(this);

    // Instancia o DAO para comunicação com a API
    m_dao = new LancamentoDAO(this);

    // --- SETUP DO GRÁFICO DE PIZZA ---
    m_chart = new QChart();
    m_chart->setTitle("Gastos por Categoria (Mês Atual)");
    m_chart->setTheme(QChart::ChartThemeDark);
    m_chart->setAnimationOptions(QChart::AllAnimations);
    m_chart->setBackgroundVisible(false); // Fundo transparente

    // Configura a visualização do gráfico (QChartView)
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumHeight(400); // Garante altura mínima
    m_chartView->setBackgroundBrush(Qt::transparent);

    // Adiciona a visualização do gráfico ao layout definido no .ui
    ui->layoutGraficoPizza->addWidget(m_chartView);

    // --- SETUP DO NOVO GRÁFICO DE BARRAS ---
    m_chartBarras = new QChart();
    m_chartBarras->setTitle("Receitas vs. Despesas por Mês");
    m_chartBarras->setTheme(QChart::ChartThemeDark);
    m_chartBarras->setAnimationOptions(QChart::SeriesAnimations);
    m_chartBarras->setBackgroundVisible(false);

    m_chartViewBarras = new QChartView(m_chartBarras);
    m_chartViewBarras->setRenderHint(QPainter::Antialiasing);
    m_chartViewBarras->setMinimumHeight(300);
    ui->layoutGraficoBarras->addWidget(m_chartViewBarras); // Adiciona ao novo layout

    // --- SETUP DO NOVO GRÁFICO DE TENDÊNCIA ---
    m_chartTendencia = new QChart();
    m_chartTendencia->setTitle("Evolução de Gastos na Categoria");
    m_chartTendencia->setTheme(QChart::ChartThemeDark);
    m_chartTendencia->setAnimationOptions(QChart::SeriesAnimations);

    m_chartViewTendencia = new QChartView(m_chartTendencia);
    m_chartViewTendencia->setRenderHint(QPainter::Antialiasing);
    ui->layoutGraficoTendencia->addWidget(m_chartViewTendencia);

    // --- LÓGICA DE VISIBILIDADE INICIAL ---
    // Verifica o perfil no momento da criação e ajusta a visibilidade da aba DRE.
    QString tipoPerfil = SessionManager::instance().getTipoPerfil();
    bool isPerfilPJ = (tipoPerfil == "PJ");
    ui->tabDre->setVisible(isPerfilPJ);
    ui->tabFluxoCaixa->setVisible(isPerfilPJ);
    configurarTabelaDre();
    configurarTabelaFluxoCaixa();

    // 4. Conecta os sinais do DAO aos slots desta classe
    connect(m_dao, &LancamentoDAO::contasRecebidas, this, &pageRelatorios::onContasRecebidas);
    connect(m_dao, &LancamentoDAO::gastosPorCategoriaRecebidos, this, &pageRelatorios::onGastosRecebidos);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &pageRelatorios::onErroDeRede);
    connect(m_dao, &LancamentoDAO::lancamentosRecebidos, this, &pageRelatorios::onDetalhesRecebidos);
    connect(m_dao, &LancamentoDAO::comparativoMensalRecebido, this, &pageRelatorios::onComparativoRecebido);
    connect(m_dao, &LancamentoDAO::categoriasRecebidas, this, &pageRelatorios::onCategoriasDespesaRecebidas); // Reutilizamos o sinal
    connect(m_dao, &LancamentoDAO::tendenciaCategoriaRecebida, this, &pageRelatorios::onTendenciaRecebida);
    connect(m_dao, &LancamentoDAO::dreRecebido, this, &pageRelatorios::onDreRecebido);
    connect(m_dao, &LancamentoDAO::fluxoCaixaRecebido, this, &pageRelatorios::onFluxoCaixaRecebido);

    // Define as datas padrão nos QDateEdit
    QDate dataAtual = QDate::currentDate();
    QDate primeiroDiaDoMes = QDate(dataAtual.year(), dataAtual.month(), 1);

    ui->dateEditInicio->setDate(primeiroDiaDoMes);
    ui->dateEditFim->setDate(dataAtual);

    // --- CONFIGURAÇÃO DO NOVO FILTRO DE PERÍODO ---
    // Conecta o novo ComboBox de Período ao nosso novo slot
    connect(ui->comboBoxPeriodo, &QComboBox::currentIndexChanged, this, &pageRelatorios::onPeriodoSelecionado);
    // Preenche o ComboBox com as opções de período
    ui->comboBoxPeriodo->addItem("Mês Atual", 0); // O segundo parâmetro é um ID que usaremos
    ui->comboBoxPeriodo->addItem("Mês Passado", 1);
    ui->comboBoxPeriodo->addItem("Últimos 3 Meses", 2);
    ui->comboBoxPeriodo->addItem("Este Ano", 3);
    ui->comboBoxPeriodo->addItem("Período Personalizado", 4);

    // Conecta o botão "Filtrar" para recarregar os dados
    connect(ui->buttonFiltrar, &QPushButton::clicked, this, &pageRelatorios::carregarDados);

    // Configura o cabeçalho da nova tabela
    ui->tableWidgetDetalhes->setColumnCount(4);
    ui->tableWidgetDetalhes->setHorizontalHeaderLabels({"Data", "Descrição", "Categoria", "Valor"});
    ui->tableWidgetDetalhes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // No final do construtor, peça a lista de contas para preencher o combobox
    QString token = SessionManager::instance().getToken();
    m_dao->obterTodasContas(token);
    m_dao->obterTodasCategorias(token);

}

pageRelatorios::~pageRelatorios()
{
    delete ui;
}

void pageRelatorios::carregarDados()
{
    // --- LÓGICA DE VISIBILIDADE ATUALIZADA ---
    // Reavalia a visibilidade da aba DRE toda vez que os dados são carregados.
    QString tipoPerfil = SessionManager::instance().getTipoPerfil();
    bool isPerfilPJ = (tipoPerfil == "PJ");

    int dreIndex = ui->tabWidget->indexOf(ui->tabDre);
    if (dreIndex != -1) ui->tabWidget->setTabVisible(dreIndex, isPerfilPJ);

    int fluxoCaixaIndex = ui->tabWidget->indexOf(ui->tabFluxoCaixa);
    if (fluxoCaixaIndex != -1) ui->tabWidget->setTabVisible(fluxoCaixaIndex, isPerfilPJ);

    // --- LÓGICA PARA TÍTULO DINÂMICO ---
    QString periodoTexto = ui->comboBoxPeriodo->currentText();
    QString novoTituloPizza;

    if (periodoTexto == "Período Personalizado") {
        novoTituloPizza = "Gastos por Categoria (Personalizado)";
    } else {
        novoTituloPizza = QString("Gastos por Categoria (%1)").arg(periodoTexto);
    }
    m_chart->setTitle(novoTituloPizza);
    // ------------------------------------

    qDebug() << "pageRelatorios: Requisitando dados de gastos por categoria...";
    QString token = SessionManager::instance().getToken();
    if (token.isEmpty()) {
        qDebug() << "pageRelatorios: Token inválido, carregamento cancelado.";
        return;
    }

    // Lê os valores dos filtros da UI
    QDate dataInicio = ui->dateEditInicio->date();
    QDate dataFim = ui->dateEditFim->date();
    // Pega o ID da conta do item selecionado no ComboBox
    int idConta = ui->comboBoxConta->currentData().toInt();

    // Chama o método do DAO com os filtros
    m_dao->obterGastosPorCategoria(token, dataInicio, dataFim, idConta);
    //busca os dados da tabela
    m_dao->obterTodos(token, dataInicio, dataFim, idConta);
    // Adiciona a chamada para o novo gráfico
    m_dao->obterComparativoMensal(token, dataInicio, dataFim, idConta);

    if (isPerfilPJ) {
        m_dao->obterDre(token, dataInicio, dataFim);
        m_dao->obterFluxoCaixa(token, dataInicio, dataFim); // <-- ADICIONE A CHAMADA
    }
}

void pageRelatorios::onGastosRecebidos(const QHash<QString, double>& dados)
{
    qDebug() << "pageRelatorios: Dados de gastos recebidos, atualizando gráfico.";
    m_chart->removeAllSeries(); // Limpa dados antigos

    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35); // Cria um efeito de "Donut Chart"
    series->setPieSize(0.7);   // Deixa uma margem em volta do gráfico

    // Adiciona os dados da API na série do gráfico
    for(auto it = dados.constBegin(); it != dados.constEnd(); ++it) {
        series->append(it.key(), it.value());
    }

    // Percorre cada "fatia" do gráfico para personalizá-la
    for(QPieSlice *slice : series->slices()) {
        slice->setLabelVisible(); // Garante que o rótulo seja visível
        slice->setLabelColor(Qt::white);
        // Assume que o valor total do gráfico está na moeda principal (BRL)
        QString simboloPrincipal = "R$";
        slice->setLabel(QString("%1\n %2 %3 \n (%4%)")
            .arg(slice->label())
            .arg(simboloPrincipal) // Usa a variável
            .arg(slice->value(), 0, 'f', 2) // Formata com 2 casas decimais
            .arg(slice->percentage() * 100, 0, 'f', 1));

        // Efeito visual: ao passar o mouse, a fatia "explode" e a cor muda
        connect(slice, &QPieSlice::hovered, this, [=](bool hovered){
            if (hovered) {
                slice->setExploded(true);
                slice->setLabelFont(QFont("Arial", 11, QFont::Bold));
            } else {
                slice->setExploded(false);
                slice->setLabelFont(QFont("Arial", 9));
            }
        });
        connect(slice, &QPieSlice::clicked, this, [this, slice](){
            filtrarTabelaPorCategoria(slice->label().split("\n").first()); // Pega só o nome da categoria
        });
    }

    m_chart->addSeries(series);
}

void pageRelatorios::onContasRecebidas(const QVector<Conta>& contas)
{
    ui->comboBoxConta->clear();
    // Adiciona a opção "Todas" que terá o ID -1
    ui->comboBoxConta->addItem("Todas as Contas", -1);
    for (const auto& conta : contas) {
        ui->comboBoxConta->addItem(conta.nome, conta.id);
    }
    carregarDados();
}

void pageRelatorios::onErroDeRede(const QString& motivo)
{
    QMessageBox::warning(this, "Erro de Rede", "Não foi possível carregar os dados para os relatórios: " + motivo);
}

void pageRelatorios::onDetalhesRecebidos(const QVector<Lancamento>& lancamentos)
{
    m_lancamentosDoPeriodo = lancamentos; // Salva a lista completa
    popularTabelaDetalhes(m_lancamentosDoPeriodo); // Popula a tabela com todos os dados
}

void pageRelatorios::onComparativoRecebido(const QVector<ResumoMensal>& resumo)
{
    m_chartBarras->removeAllSeries();
    if(m_chartBarras->axisX()) m_chartBarras->removeAxis(m_chartBarras->axisX());
    if(m_chartBarras->axisY()) m_chartBarras->removeAxis(m_chartBarras->axisY());

    QBarSet *setReceitas = new QBarSet("Receitas");
    QBarSet *setDespesas = new QBarSet("Despesas");
    setReceitas->setColor(QColor("#2ecc71"));
    setDespesas->setColor(QColor("#e74c3c"));

    QStringList categories;

    for(const auto& r : resumo) {
        *setReceitas << r.receitas;
        *setDespesas << r.despesas;
        categories << r.mes;
    }

    QBarSeries *series = new QBarSeries();
    series->append(setReceitas);
    series->append(setDespesas);

    m_chartBarras->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    m_chartBarras->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    m_chartBarras->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    m_chartBarras->legend()->setVisible(true);
    m_chartBarras->legend()->setAlignment(Qt::AlignBottom);
}

void pageRelatorios::popularTabelaDetalhes(const QVector<Lancamento>& lancamentos)
{
    ui->tableWidgetDetalhes->setRowCount(0);
    for(const auto& lancamento : lancamentos) {
        int linha = ui->tableWidgetDetalhes->rowCount();
        ui->tableWidgetDetalhes->insertRow(linha);

        ui->tableWidgetDetalhes->setItem(linha, 0, new QTableWidgetItem(lancamento.data_lancamento.toString("dd/MM/yyyy")));
        ui->tableWidgetDetalhes->setItem(linha, 1, new QTableWidgetItem(lancamento.descricao));
        ui->tableWidgetDetalhes->setItem(linha, 2, new QTableWidgetItem(lancamento.nome_categoria));

        QString simbolo = "R$"; // Padrão
        if (lancamento.moeda_codigo_original == "USD") {
            simbolo = "$";
        } else if (lancamento.moeda_codigo_original == "EUR") {
            simbolo = "€";
        } // Adicione mais moedas aqui

        QString valorFormatado = QString("%1 %2").arg(simbolo).arg(lancamento.valor_original, 0, 'f', 2);
        QTableWidgetItem *itemValor = new QTableWidgetItem(valorFormatado);
        itemValor->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        if (lancamento.tipo == "Receita") {
            itemValor->setForeground(QColor("#2ecc71"));
        } else {
            itemValor->setForeground(QColor("#e74c3c"));
        }
        ui->tableWidgetDetalhes->setItem(linha, 3, itemValor);
    }
}

void pageRelatorios::filtrarTabelaPorCategoria(const QString& nomeCategoria)
{
    QVector<Lancamento> lancamentosFiltrados;
    for(const auto& lancamento : m_lancamentosDoPeriodo) {
        if(lancamento.nome_categoria == nomeCategoria) {
            lancamentosFiltrados.append(lancamento);
        }
    }
    popularTabelaDetalhes(lancamentosFiltrados); // Usa a mesma função de popular
}


void pageRelatorios::onPeriodoSelecionado(int index)
{
    QDate dataAtual = QDate::currentDate();
    QDate dataInicio;
    QDate dataFim = dataAtual;

    int idPeriodo = ui->comboBoxPeriodo->itemData(index).toInt();

    switch (idPeriodo) {
    case 0: // Mês Atual
        dataInicio = QDate(dataAtual.year(), dataAtual.month(), 1);
        break;
    case 1: // Mês Passado
        {
            QDate mesPassado = dataAtual.addMonths(-1);
            dataInicio = QDate(mesPassado.year(), mesPassado.month(), 1);
            dataFim = QDate(mesPassado.year(), mesPassado.month(), mesPassado.daysInMonth());
        }
        break;
    case 2: // Últimos 3 Meses
        dataInicio = dataAtual.addMonths(-3);
        break;
    case 3: // Este Ano
        dataInicio = QDate(dataAtual.year(), 1, 1);
        break;
    case 4: // Período Personalizado
        // Habilita os QDateEdits e não faz nada, deixa o usuário escolher
        ui->dateEditInicio->setEnabled(true);
        ui->dateEditFim->setEnabled(true);
        return; // Sai da função para não chamar carregarDados() ainda
    }

    // Para os períodos pré-definidos, atualiza os QDateEdits e os desabilita
    ui->dateEditInicio->setDate(dataInicio);
    ui->dateEditFim->setDate(dataFim);
    ui->dateEditInicio->setEnabled(false);
    ui->dateEditFim->setEnabled(false);

    // Chama a função para recarregar os gráficos e a tabela
    carregarDados();
}

void pageRelatorios::on_buttonExportarCSV_clicked()
{
    if (m_lancamentosDoPeriodo.isEmpty()) {
        QMessageBox::information(this, "Exportar", "Não há dados para exportar.");
        return;
    }

    QString caminhoArquivo = QFileDialog::getSaveFileName(this, "Salvar como", QDir::homePath(), "Arquivos CSV (*.csv)");

    if (caminhoArquivo.isEmpty()) {
        return; // O utilizador cancelou
    }

    QFile file(caminhoArquivo);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erro", "Não foi possível criar ou abrir o ficheiro para escrita.");
        return;
    }

    QTextStream stream(&file);

    // Cabeçalho corrigido
    stream << "\"Data\",\"Descrição\",\"Categoria\",\"Valor\",\"Tipo\"\n";

    QLocale brLocale(QLocale::Portuguese, QLocale::Brazil);

    // --- ESCRITA DOS DADOS COM CORREÇÃO DE CONSTÂNCIA ---
    for (const auto& lancamento : m_lancamentosDoPeriodo) {
        // 1. Cria cópias locais e não-constantes das strings
        QString descricaoLimpa = lancamento.descricao;
        QString nomeCategoriaLimpo = lancamento.nome_categoria;

        // 2. Modifica e usa as cópias
        QStringList rowData;
        rowData << "\"" + lancamento.data_lancamento.toString("dd/MM/yyyy") + "\"";
        rowData << "\"" + descricaoLimpa.replace("\"", "\"\"") + "\"";
        rowData << "\"" + nomeCategoriaLimpo.replace("\"", "\"\"") + "\"";
        rowData << "\"" + brLocale.toCurrencyString(lancamento.valor_original) + "\"";
        rowData << "\"" + lancamento.tipo + "\"";

        stream << rowData.join(',') << "\n";
    }
    // --- FIM DA CORREÇÃO ---

    file.close();
    QMessageBox::information(this, "Sucesso", "Dados exportados com sucesso para:\n" + caminhoArquivo);
}
void pageRelatorios::onCategoriasDespesaRecebidas(const QVector<Categoria>& categorias)
{
    // Popula o ComboBox de tendência apenas com categorias de despesa
    ui->comboCategoriaTendencia->clear();
    for (const auto& categoria : categorias) {
        if (categoria.tipo == "Despesa") {
            ui->comboCategoriaTendencia->addItem(categoria.nome, categoria.id);
        }
    }
}

void pageRelatorios::on_buttonAnalisarTendencia_clicked()
{
    int idCategoria = ui->comboCategoriaTendencia->currentData().toInt();
    if (idCategoria > 0) {
        QString token = SessionManager::instance().getToken();
        m_dao->obterTendenciaCategoria(idCategoria, token);
    }
}

void pageRelatorios::onTendenciaRecebida(const QVector<PontoTendencia>& tendencia)
{
    m_chartTendencia->removeAllSeries();
    if(m_chartTendencia->axisX()) m_chartTendencia->removeAxis(m_chartTendencia->axisX());
    if(m_chartTendencia->axisY()) m_chartTendencia->removeAxis(m_chartTendencia->axisY());

    QLineSeries *series = new QLineSeries();
    QString nomeCategoria = ui->comboCategoriaTendencia->currentText();
    series->setName(nomeCategoria);

    QStringList categories;
    double maxVal = 0;

    for (const auto& ponto : tendencia) {
        series->append(categories.size(), ponto.total);
        categories << ponto.mes;
        if (ponto.total > maxVal) maxVal = ponto.total;
    }

    m_chartTendencia->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    m_chartTendencia->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxVal * 1.1); // Range com uma folga de 10%
    axisY->setLabelFormat("R$ %.0f");
    m_chartTendencia->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    m_chartTendencia->legend()->setVisible(true);
}

void pageRelatorios::configurarTabelaDre()
{
    ui->tableWidgetDre->setColumnCount(2);
    ui->tableWidgetDre->setHorizontalHeaderLabels({"Conta", "Valor"});
    ui->tableWidgetDre->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidgetDre->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidgetDre->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetDre->verticalHeader()->setVisible(false);
}

void pageRelatorios::onDreRecebido(const DreData& dre)
{
    popularTabelaDre(dre);
}

void pageRelatorios::popularTabelaDre(const DreData& dre)
{
    ui->tableWidgetDre->setRowCount(0);
    QLocale brLocale(QLocale::Portuguese, QLocale::Brazil);

    // Função auxiliar para adicionar uma linha na tabela
    auto adicionarLinha = [&](const QString& conta, double valor, bool isSubtotal = false, bool isResultado = false) {
        int linha = ui->tableWidgetDre->rowCount();
        ui->tableWidgetDre->insertRow(linha);

        QTableWidgetItem* itemConta = new QTableWidgetItem(conta);
        QTableWidgetItem* itemValor = new QTableWidgetItem(brLocale.toCurrencyString(valor));
        itemValor->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        if (isSubtotal || isResultado) {
            QFont font;
            font.setBold(true);
            itemConta->setFont(font);
            itemValor->setFont(font);
        }
        if (isResultado) {
            QColor cor = (valor >= 0) ? QColor("#2ecc71") : QColor("#e74c3c"); // Verde ou Vermelho
            itemValor->setForeground(cor);
        }

        ui->tableWidgetDre->setItem(linha, 0, itemConta);
        ui->tableWidgetDre->setItem(linha, 1, itemValor);
    };

    // Popula a tabela na ordem correta do DRE
    adicionarLinha("Receita Bruta", dre["Receita Bruta"]);
    adicionarLinha("(-) Deduções da Receita", -dre["Dedução da Receita"]);
    adicionarLinha("= Receita Líquida", dre["Receita Líquida"], true);
    adicionarLinha("(-) Custo do Serviço/Produto", -dre["Custo do Serviço/Produto"]);
    adicionarLinha("= Lucro Bruto", dre["Lucro Bruto"], true);
    adicionarLinha("(-) Despesa Operacional", -dre["Despesa Operacional"]);
    adicionarLinha("= Lucro Operacional", dre["Lucro Operacional"], true);
    adicionarLinha("(+) Receita Financeira", dre["Receita Financeira"]);
    adicionarLinha("(-) Despesa Financeira", -dre["Despesa Financeira"]);
    adicionarLinha("= Resultado Antes dos Impostos", dre["Resultado Antes dos Impostos"], true);
    adicionarLinha("(-) Imposto sobre o Lucro", -dre["Imposto sobre o Lucro"]);
    adicionarLinha("= Lucro Líquido", dre["Lucro Líquido"], false, true);
}

void pageRelatorios::configurarTabelaFluxoCaixa()
{
    ui->tableWidgetFluxoCaixa->setColumnCount(2);
    ui->tableWidgetFluxoCaixa->setHorizontalHeaderLabels({"Descrição", "Valor (BRL)"});
    ui->tableWidgetFluxoCaixa->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidgetFluxoCaixa->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidgetFluxoCaixa->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetFluxoCaixa->verticalHeader()->setVisible(false);
}

void pageRelatorios::onFluxoCaixaRecebido(const FluxoCaixaData& fluxoCaixa)
{
    popularTabelaFluxoCaixa(fluxoCaixa);
}

void pageRelatorios::popularTabelaFluxoCaixa(const FluxoCaixaData& fluxoCaixa)
{
    // --- CORREÇÃO CRÍTICA AQUI ---
    // Garante que estamos limpando e usando a tabela correta: tableWidgetFluxoCaixa
    ui->tableWidgetFluxoCaixa->setRowCount(0);
    QLocale brLocale(QLocale::Portuguese, QLocale::Brazil);

    // A função auxiliar agora aponta para a tabela correta
    auto adicionarLinha = [&](const QString& conta, double valor, bool isSubtotal = false, bool isResultado = false) {
        // Aponta para a tabela correta
        int linha = ui->tableWidgetFluxoCaixa->rowCount();
        ui->tableWidgetFluxoCaixa->insertRow(linha);

        QTableWidgetItem* itemConta = new QTableWidgetItem(conta);
        QTableWidgetItem* itemValor = new QTableWidgetItem(brLocale.toCurrencyString(valor));
        itemValor->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        if (isSubtotal || isResultado) {
            QFont font;
            font.setBold(true);
            itemConta->setFont(font);
            itemValor->setFont(font);
        }
        if (isResultado) {
            QColor cor = (valor >= 0) ? QColor("#2ecc71") : QColor("#e74c3c");
            itemValor->setForeground(cor);
        }

        // Adiciona os itens à tabela correta
        ui->tableWidgetFluxoCaixa->setItem(linha, 0, itemConta);
        ui->tableWidgetFluxoCaixa->setItem(linha, 1, itemValor);
    };
    // --- FIM DA CORREÇÃO ---

    // A lógica para popular as linhas continua a mesma
    adicionarLinha("Saldo Inicial do Período", fluxoCaixa.value("Saldo Inicial"));
    adicionarLinha("(+) Total de Entradas", fluxoCaixa.value("Total de Entradas"));
    adicionarLinha("(-) Total de Saídas", -fluxoCaixa.value("Total de Saídas"));
    adicionarLinha("= Fluxo de Caixa Líquido", fluxoCaixa.value("Fluxo de Caixa Líquido"), true, true);
    adicionarLinha("= Saldo Final do Período", fluxoCaixa.value("Saldo Final"), true);
}