#include "pageLancamentos.h"
#include "ui_pageLancamentos.h"
#include "Designer/FormsDashboard/FormsLancamentos/formAdicionarLancamento.h"
#include "Designer/FormsDashboard/FormsLancamentos/dialogImportarExtrato.h"
#include "Modelo/TransacaoImportada.h"
#include "Designer/FormsDashboard/FormsLancamentos/dialogMapeamento.h"
#include "DataAccess/LancamentoDAO.h"
#include "DataAccess/ContaDAO.h"
#include "Gerenciamento/SessionManager.h" // Inclui nosso "cofre" de sessão
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QTextStream>
#include <QFile>
#include <QLocale>
#include <QRegularExpression>

pageLancamentos::pageLancamentos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageLancamentos)
{
    ui->setupUi(this);
    m_dialogoAdicionar = nullptr;

    // Cria uma única instância do DAO para esta página
    m_dao = new LancamentoDAO(this);
    m_contaDAO = new ContaDAO(this);

    // Conecta os sinais de resultado do DAO aos nossos slots
    connect(m_dao, &LancamentoDAO::lancamentosRecebidos, this, &pageLancamentos::onLancamentosRecebidos);
    connect(m_dao, &LancamentoDAO::onLancamentoError, this, &pageLancamentos::onErroDeRede);
    connect(m_contaDAO, &ContaDAO::onContaError, this, &pageLancamentos::onErroDeRede);
    connect(m_dao, &LancamentoDAO::lancamentoModificadoComSucesso, this, &pageLancamentos::carregarTabela);
    connect(m_dao, &LancamentoDAO::lancamentoExcluidoComSucesso, this, &pageLancamentos::carregarTabela);
    // Conecta o slot para popular o ComboBox de contas
    connect(m_contaDAO, &ContaDAO::contasRecebidas, this, &pageLancamentos::onContasRecebidas);
    connect(m_dao, &LancamentoDAO::ocrProcessadoComSucesso, this, &pageLancamentos::onOcrConcluido);
    connect(m_dao, &LancamentoDAO::sugestoesRecebidas, this, &pageLancamentos::onSugestoesParaMapeamentoRecebidas);

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
    m_contaDAO->obterTodasContas(token);

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

        // Agora, quando o lançamento for salvo, nós recarregamos a tabela E fechamos o diálogo.
        connect(m_dialogoAdicionar, &formAdicionarLancamento::lancamentoSalvo, this, [this]() {
            this->carregarTabela();
            if (m_dialogoAdicionar) {
                m_dialogoAdicionar->accept(); // Fecha o diálogo com sucesso
            }
        });

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

    // A mesma lógica de recarregar e depois fechar
    connect(form, &formAdicionarLancamento::lancamentoSalvo, this, [this, form]() {
        this->carregarTabela();
        form->accept();
    });

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
        m_idContaImportacao = dialogoInicial.idContaSelecionada();

        if (caminho.isEmpty() || m_idContaImportacao <= 0) {
            QMessageBox::warning(this, "Seleção Inválida", "Por favor, selecione um arquivo e uma conta de destino.");
            return;
        }

        if (caminho.endsWith(".pdf", Qt::CaseInsensitive))
        {
            // A sua lógica para processar PDFs continua aqui, sem alterações...
            qDebug() << "Arquivo PDF selecionado. Enviando para o servidor para processamento OCR...";
            QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, "Processando Extrato", "Aguarde, o sistema está lendo o seu extrato em PDF...", QMessageBox::NoButton, this);
            msgBox->setAttribute(Qt::WA_DeleteOnClose);
            msgBox->show();
            disconnect(m_dao, &LancamentoDAO::ocrProcessadoComSucesso, this, &pageLancamentos::onOcrConcluido);
            connect(m_dao, &LancamentoDAO::ocrProcessadoComSucesso, this, [=](const QVector<TransacaoImportada>& transacoes) {
                msgBox->close();
                onOcrConcluido(transacoes);
            });
            QString token = SessionManager::instance().getToken();
            m_dao->processarExtratoOcr(caminho, token);
        }
        else if (caminho.endsWith(".csv", Qt::CaseInsensitive))
        {
            qDebug() << "Arquivo CSV selecionado. Lendo o arquivo localmente...";

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
                QStringList campos = linha.split(QRegularExpression(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"));
                if (campos.size() >= 5) {
                    TransacaoImportada t;
                    t.dataStr = campos[0];
                    t.descricaoStr = campos[1];
                    t.categoriaStr = campos[2];
                    t.valorStr = campos[3];
                    t.tipoStr = campos[4];
                    transacoesLidas.append(t);
                }
            }
            file.close();

            // Se leu transações, agora pedimos sugestões ANTES de mostrar a tela
            if (!transacoesLidas.isEmpty()) {
                // 1. Guarda as transações lidas em uma variável de membro
                m_transacoesLidas = transacoesLidas;

                // 2. Extrai apenas as descrições para enviar à API
                QVector<QString> descricoes;
                for (const auto& t : m_transacoesLidas) {
                    // Limpa as aspas aqui para garantir que a busca no mapa funcione depois
                    QString descricaoLimpa = t.descricaoStr;
                    descricoes.append(descricaoLimpa.remove('"').trimmed());
                }

                // 3. Chama o DAO para buscar as sugestões
                QString token = SessionManager::instance().getToken();
                m_dao->obterSugestoesCategorias(descricoes, token);

                // O processo para aqui e continua no slot onSugestoesParaMapeamentoRecebidas...
            } else {
                QMessageBox::information(this, "Importação", "Nenhuma transação válida encontrada no arquivo.");
            }
        }

        else
        {
            QMessageBox::warning(this, "Arquivo Inválido", "Por favor, selecione um arquivo com formato válido (.csv ou .pdf).");
        }
    }
}

void pageLancamentos::onSugestoesParaMapeamentoRecebidas(const QMap<QString, int>& sugestoes)
{


    // 1. Abre o diálogo de mapeamento, AGORA com as sugestões recebidas da API
    dialogMapeamento dialogoMap(m_transacoesLidas, sugestoes, this);
    if (dialogoMap.exec() == QDialog::Accepted)
    {
        // 2. Se o usuário confirmar, continua com a lógica de salvar no banco
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
            // ATENÇÃO: Use a variável de membro que você criou para o ID da conta.
            // Ex: novoLancamento.id_conta = m_idContaImportacao;
            novoLancamento.id_conta = m_idContaImportacao;
            novoLancamento.id_categoria = transacaoImportada.id_categoria;
            novoLancamento.id_meta = -1;

            // Cria cópias locais para modificação segura
            QString descricaoLimpa = transacaoImportada.descricaoStr;
            QString dataLimpa = transacaoImportada.dataStr;
            novoLancamento.descricao = descricaoLimpa.remove('"').trimmed();
            novoLancamento.data_lancamento = QDate::fromString(dataLimpa.remove('"').trimmed(), "dd/MM/yyyy");

            // Correção para o tipo (que já estava no seu código)
            QString tipoLimpo = transacaoImportada.tipoStr;
            novoLancamento.tipo = tipoLimpo.remove('"').trimmed();

            // Lógica de conversão de valor (que já estava no seu código)
            QString valorStr = transacaoImportada.valorStr;
            valorStr = valorStr.remove(QRegularExpression("[^\\d,.-]"));

            valorStr.replace(',', '.');

            bool ok;
            double valor = valorStr.toDouble(&ok);

            if (!ok) {
                qDebug() << "Falha ao converter o valor '" << transacaoImportada.valorStr << "' -> '" << valorStr << "'";
                ignoradoCount++;
                continue;
            }

            novoLancamento.valor = valor;
            novoLancamento.valor_original = valor;

            novoLancamento.moeda_codigo_original = "BRL";
            novoLancamento.taxa_cambio_usada = 1;

            m_dao->adicionarLancamento(novoLancamento, token);
            sucessoCount++;
        }

        QMessageBox::information(this, "Importação Concluída",
            QString("Importação finalizada com sucesso!\n\n%1 lançamentos importados.\n%2 linhas ignoradas.")
            .arg(sucessoCount)
            .arg(ignoradoCount));

        carregarTabela();
    }

    // 3. Limpa a variável temporária
    m_transacoesLidas.clear();
}

// Adicione o novo slot para lidar com a resposta do OCR
void pageLancamentos::onOcrConcluido(const QVector<TransacaoImportada>& transacoes)
{
    if (transacoes.isEmpty()) {
        QMessageBox::information(this, "Processamento OCR", "O extrato foi lido, mas nenhuma transação foi encontrada no texto.\n\nTente usar um extrato com um layout mais simples ou verifique o parser no backend.");
        return;
    }

    QMessageBox::information(this, "OCR Concluído", QString("%1 transações foram encontradas no PDF! Agora, vamos categorizá-las.").arg(transacoes.size()));

    // --- LÓGICA IDÊNTICA À DO CSV ---
    // Inicia o mesmo fluxo de pedido de sugestões que já usamos para o CSV.
    m_transacoesLidas = transacoes;

    QVector<QString> descricoes;
    for (const auto& t : m_transacoesLidas) {
        QString descricaoLimpa = t.descricaoStr;
        descricoes.append(descricaoLimpa.remove('"').trimmed());
    }

    QString token = SessionManager::instance().getToken();
    m_dao->obterSugestoesCategorias(descricoes, token);
    // O processo continua no slot onSugestoesParaMapeamentoRecebidas...
}


