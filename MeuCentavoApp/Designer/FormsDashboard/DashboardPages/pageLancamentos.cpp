#include "pageLancamentos.h"
#include "ui_pageLancamentos.h"
#include "Designer/FormsDashboard/FormsLancamentos/formAdicionarLancamento.h"
#include "Designer/FormsDashboard/FormsLancamentos/dialogImportarExtrato.h"
#include "Modelo/TransacaoImportada.h"
#include "Designer/FormsDashboard/FormsLancamentos/dialogMapeamento.h"
#include "DataAccess/LancamentoDAO.h"
#include "Gerenciamento/SessionManager.h" // Inclui nosso "cofre" de sessão
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QTextStream>
#include <QFile>
#include <QLocale>

pageLancamentos::pageLancamentos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageLancamentos)
{
    ui->setupUi(this);
    m_dialogoAdicionar = nullptr;

    // Cria uma única instância do DAO para esta página
    m_dao = new LancamentoDAO(this);

    // Conecta os sinais de resultado do DAO aos nossos slots
    connect(m_dao, &LancamentoDAO::lancamentosRecebidos, this, &pageLancamentos::onLancamentosRecebidos);
    connect(m_dao, &LancamentoDAO::erroOcorrido, this, &pageLancamentos::onErroDeRede);
    connect(m_dao, &LancamentoDAO::lancamentoExcluidoComSucesso, this, &pageLancamentos::carregarTabela);
    // Conecta o slot para popular o ComboBox de contas
    connect(m_dao, &LancamentoDAO::contasRecebidas, this, &pageLancamentos::onContasRecebidas);

    // Conecta o botão da UI ao slot que abre o diálogo
    connect(ui->buttonAdicionarLancamento, &QPushButton::clicked, this, &pageLancamentos::abrirDialogoAdicionar);

    // Configuração inicial da tabela
    ui->tabelaTodosLancamentos->setColumnCount(7);
    ui->tabelaTodosLancamentos->setHorizontalHeaderLabels({"Data", "Descrição", "Conta", "Categoria", "Tipo", "Valor", "Ações"});
    QHeaderView* header = ui->tabelaTodosLancamentos->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents); // Data
    header->setSectionResizeMode(1, QHeaderView::Stretch);           // Descrição (estica)
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Conta
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Categoria
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents); // Tipo
    header->setSectionResizeMode(5, QHeaderView::Interactive); // Valor
    header->setSectionResizeMode(6, QHeaderView::ResizeToContents); // Ações

    //AUMENTO DA COLUNA VALOR
    ui->tabelaTodosLancamentos->setColumnWidth(5, 120);

    // Define datas padrão
    QDate dataAtual = QDate::currentDate();
    QDate primeiroDiaDoMes = QDate(dataAtual.year(), dataAtual.month(), 1);
    ui->dateEditInicio->setDate(primeiroDiaDoMes);
    ui->dateEditFim->setDate(dataAtual);

    // O botão Filtrar agora que chama o carregamento da tabela
    connect(ui->buttonFiltrar, &QPushButton::clicked, this, &pageLancamentos::carregarTabela);
    // Carrega a lista de contas para o filtro ao iniciar
    QString token = SessionManager::instance().getToken();
    m_dao->obterTodasContas(token);

}

pageLancamentos::~pageLancamentos()
{
    delete ui;
}

void pageLancamentos::abrirDialogoAdicionar()
{
    if (!m_dialogoAdicionar) {
        // O diálogo agora também não precisa de parâmetros, pois ele pegará o ID do SessionManager
        m_dialogoAdicionar = new formAdicionarLancamento(this);
        m_dialogoAdicionar->setAttribute(Qt::WA_DeleteOnClose);

        // Conectamos o sinal de sucesso do diálogo ao nosso slot que recarrega a tabela
        connect(m_dialogoAdicionar, &formAdicionarLancamento::lancamentoSalvo, this, &pageLancamentos::carregarTabela);

        // Limpamos o ponteiro quando o diálogo for destruído
        connect(m_dialogoAdicionar, &QObject::destroyed, [this](){ m_dialogoAdicionar = nullptr; });
    }
    m_dialogoAdicionar->open();
}

void pageLancamentos::carregarTabela()
{
    qDebug() << "pageLancamentos: Requisitando lista de lançamentos da API...";
    QString token = SessionManager::instance().getToken();
    if (token.isEmpty()) return;

    // Lê os valores dos filtros da UI
    QDate dataInicio = ui->dateEditInicio->date();
    QDate dataFim = ui->dateEditFim->date();
    int idConta = ui->comboBoxConta->currentData().toInt();
    // Imprime os filtros exatos que estão sendo enviados para o DAO
    qDebug() << "Filtros enviados -> Início:" << dataInicio.toString("yyyy-MM-dd")
             << "| Fim:" << dataFim.toString("yyyy-MM-dd")
             << "| ID da Conta:" << idConta;
    // Chama a versão CORRETA da função, com todos os parâmetros
    m_dao->obterTodos(token, dataInicio, dataFim, idConta);
    emit dadosAtualizados();
}

void pageLancamentos::onLancamentosRecebidos(const QVector<Lancamento>& lancamentos)
{
    qDebug() << "pageLancamentos: Lista com" << lancamentos.count() << "lançamentos recebida. Atualizando tabela.";

    ui->tabelaTodosLancamentos->blockSignals(true);
    ui->tabelaTodosLancamentos->setRowCount(0);

    for (const auto& lancamento : lancamentos) {
        int linha = ui->tabelaTodosLancamentos->rowCount();
        ui->tabelaTodosLancamentos->insertRow(linha);

        // --- Coluna 0: Data ---
        QTableWidgetItem *itemData = new QTableWidgetItem(lancamento.data_lancamento.toString("dd/MM/yyyy"));
        itemData->setTextAlignment(Qt::AlignCenter);
        ui->tabelaTodosLancamentos->setItem(linha, 0, itemData);

        // --- Coluna 1: Descrição ---
        ui->tabelaTodosLancamentos->setItem(linha, 1, new QTableWidgetItem(lancamento.descricao));

        // --- Coluna 2: Conta (COM ALINHAMENTO CORRIGIDO) ---
        QTableWidgetItem *itemConta = new QTableWidgetItem(lancamento.nome_conta);
        itemConta->setTextAlignment(Qt::AlignCenter);
        ui->tabelaTodosLancamentos->setItem(linha, 2, itemConta);

        // --- Coluna 3: Categoria (COM ALINHAMENTO CORRIGIDO) ---
        QTableWidgetItem *itemCategoria = new QTableWidgetItem(lancamento.nome_categoria);
        itemCategoria->setTextAlignment(Qt::AlignCenter);
        ui->tabelaTodosLancamentos->setItem(linha, 3, itemCategoria);

        // --- Coluna 4: Tipo (COM ALINHAMENTO CORRIGIDO) ---
        QTableWidgetItem *itemTipo = new QTableWidgetItem(lancamento.tipo);
        itemTipo->setTextAlignment(Qt::AlignCenter);
        ui->tabelaTodosLancamentos->setItem(linha, 4, itemTipo);

        // --- Coluna 5: Valor ---
        QString simbolo = "R$"; // Padrão
        if (lancamento.moeda_codigo_original == "USD") {
            simbolo = "$";
        } else if (lancamento.moeda_codigo_original == "EUR") {
            simbolo = "€";
        } // Adicione mais moedas aqui

        // Usa o valor_original que está na moeda correta
        QString valorFormatado = QString("%1 %2").arg(simbolo).arg(lancamento.valor_original, 0, 'f', 2);
        QTableWidgetItem *itemValor = new QTableWidgetItem(valorFormatado);
        itemValor->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        if (lancamento.tipo == "Receita") {
            itemValor->setForeground(QColor("#2ecc71")); // Verde
        } else {
            itemValor->setForeground(QColor("#e74c3c")); // Vermelho
        }
        ui->tabelaTodosLancamentos->setItem(linha, 5, itemValor);

        // --- Coluna 6: Ações (COM ÍNDICE CORRIGIDO) ---
        QWidget* pWidget = new QWidget();
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        pLayout->setContentsMargins(5, 0, 5, 0);
        QPushButton* btnEdit = new QPushButton("Editar");
        QPushButton* btnDelete = new QPushButton();
        btnDelete->setIcon(QIcon(":/Recursos/trash_icon.png"));
        btnEdit->setMinimumWidth(75);
        btnDelete->setFixedSize(QSize(32, 32));
        pLayout->addWidget(btnEdit);
        pLayout->addWidget(btnDelete);
        pWidget->setLayout(pLayout);
        // O widget com os botões deve ser inserido na coluna de índice 6
        ui->tabelaTodosLancamentos->setCellWidget(linha, 6, pWidget);

        // Conectar os sinais
        connect(btnEdit, &QPushButton::clicked, this, [this, lancamento](){ editarLancamento(lancamento); });
        connect(btnDelete, &QPushButton::clicked, this, [this, lancamento](){ excluirLancamento(lancamento); });
    }

    ui->tabelaTodosLancamentos->blockSignals(false);
}

void pageLancamentos::editarLancamento(const Lancamento& lancamento)
{
    // Reutilizamos o mesmo formulário de adicionar
    formAdicionarLancamento* form = new formAdicionarLancamento(this);
    form->setLancamentoParaEdicao(lancamento); // Nova função para pré-preencher

    // Conectamos o sinal de sucesso para recarregar a tabela
    connect(form, &formAdicionarLancamento::lancamentoSalvo, this, &pageLancamentos::carregarTabela);

    form->exec();
}

void pageLancamentos::excluirLancamento(const Lancamento& lancamento)
{
    QMessageBox::StandardButton resposta = QMessageBox::question(this, "Confirmar Exclusão",
        QString("Tem certeza que deseja excluir o lançamento '%1'?").arg(lancamento.descricao),
        QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        QString token = SessionManager::instance().getToken();
        m_dao->excluirLancamento(lancamento.id, token);
    }
}

void pageLancamentos::onContasRecebidas(const QVector<Conta>& contas)
{
    ui->comboBoxConta->clear();
    ui->comboBoxConta->addItem("Todas as Contas", -1);
    for (const auto& conta : contas) {
        ui->comboBoxConta->addItem(conta.nome, conta.id);
    }
    // Agora que o ComboBox está pronto, fazemos o carregamento inicial dos dados.
    carregarTabela();
}

void pageLancamentos::onErroDeRede(const QString& motivo)
{
    QMessageBox::critical(this, "Erro de Rede", "Não foi possível buscar os lançamentos:\n" + motivo);
}

void pageLancamentos::on_buttonImportarExtrato_clicked()
{
    dialogImportarExtrato dialogoInicial(this);
    if (dialogoInicial.exec() == QDialog::Accepted)
    {
        QString caminho = dialogoInicial.caminhoArquivoSelecionado();
        int idConta = dialogoInicial.idContaSelecionada();

        if (caminho.isEmpty() || idConta <= 0) {
            QMessageBox::warning(this, "Seleção Inválida", "Por favor, selecione um arquivo e uma conta de destino.");
            return;
        }

        // --- ETAPA 2: LER O ARQUIVO CSV ---
        QVector<TransacaoImportada> transacoesLidas;
        QFile file(caminho);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Erro", "Não foi possível abrir o arquivo CSV.");
            return;
        }

        QTextStream in(&file);
        in.readLine(); // Pula a linha do cabeçalho

        while (!in.atEnd()) {
            QString linha = in.readLine();
            QStringList campos = linha.split(',');

            if (campos.size() >= 4) {
                TransacaoImportada t;
                // ATENÇÃO: Ajuste os números abaixo para a ordem correta do seu arquivo
                t.dataStr = campos[0];
                t.descricaoStr = campos[1];
                t.valorEntradaStr = campos[2];
                t.valorSaidaStr = campos[3];
                transacoesLidas.append(t);
            }
        }
        file.close();

        if (transacoesLidas.isEmpty()) {
            QMessageBox::information(this, "Importação", "Nenhuma transação encontrada no arquivo.");
            return;
        }

        dialogMapeamento dialogoMap(transacoesLidas, this);
        if (dialogoMap.exec() == QDialog::Accepted) {
            // --- ETAPA FINAL: PROCESSAR E SALVAR NO BANCO ---
            QVector<TransacaoImportada> transacoesFinalizadas = dialogoMap.getTransacoesFinalizadas();
            QString token = SessionManager::instance().getToken();
            int sucessoCount = 0;
            int ignoradoCount = 0;

            for (const auto& transacaoImportada : transacoesFinalizadas) {
                if (transacaoImportada.id_categoria <= 0) {
                    ignoradoCount++;
                    continue;
                }

                Lancamento novoLancamento;
                novoLancamento.id_conta = idConta;
                novoLancamento.id_categoria = transacaoImportada.id_categoria;

                // --- CORREÇÃO DE CONSTÂNCIA APLICADA A TODAS AS STRINGS ---

                // 1. Crie cópias locais e não-constantes das strings que serão modificadas
                QString descricaoLimpa = transacaoImportada.descricaoStr;
                QString dataLimpa = transacaoImportada.dataStr;
                QString valorEntradaLimpo = transacaoImportada.valorEntradaStr;
                QString valorSaidaLimpo = transacaoImportada.valorSaidaStr;

                // 2. Agora, modifique e use as cópias
                novoLancamento.descricao = descricaoLimpa.remove('"');
                novoLancamento.data_lancamento = QDate::fromString(dataLimpa.remove('"'), "dd/MM/yyyy");

                // Lógica de limpeza de valores usando as cópias
                valorEntradaLimpo.remove('"').remove('R').remove('$').trimmed();
                valorSaidaLimpo.remove('"').remove('R').remove('$').trimmed();

                if (valorEntradaLimpo.contains(',')) {
                    valorEntradaLimpo.remove('.');
                    valorEntradaLimpo.replace(',', '.');
                }
                if (valorSaidaLimpo.contains(',')) {
                    valorSaidaLimpo.remove('.');
                    valorSaidaLimpo.replace(',', '.');
                }

                // O resto da lógica de conversão continua igual, pois já usa as cópias
                bool ok;
                double valorEntrada = valorEntradaLimpo.toDouble(&ok);
                if (ok && valorEntrada > 0) {
                    novoLancamento.valor = valorEntrada;
                    novoLancamento.tipo = "Receita";
                } else {
                    double valorSaida = valorSaidaLimpo.toDouble(&ok);
                    if (ok && valorSaida > 0) {
                        novoLancamento.valor = valorSaida;
                        novoLancamento.tipo = "Despesa";
                    } else {
                        ignoradoCount++;
                        continue;
                    }
                }

                m_dao->adicionarLancamento(novoLancamento, token);
                sucessoCount++;
            }



            QMessageBox::information(this, "Importação Concluída",
                QString("Importação finalizada com sucesso!\n\n%1 lançamentos importados.\n%2 linhas ignoradas.")
                .arg(sucessoCount)
                .arg(ignoradoCount));

            carregarTabela();
        }
    }
}
