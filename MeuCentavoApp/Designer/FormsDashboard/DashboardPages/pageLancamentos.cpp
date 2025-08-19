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
#include <QRegularExpression>

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
    connect(m_dao, &LancamentoDAO::lancamentoModificadoComSucesso, this, &pageLancamentos::carregarTabela);
    connect(m_dao, &LancamentoDAO::lancamentoExcluidoComSucesso, this, &pageLancamentos::carregarTabela);
    // Conecta o slot para popular o ComboBox de contas
    connect(m_dao, &LancamentoDAO::contasRecebidas, this, &pageLancamentos::onContasRecebidas);
    connect(m_dao, &LancamentoDAO::ocrProcessadoComSucesso, this, &pageLancamentos::onOcrConcluido);

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
        int idConta = dialogoInicial.idContaSelecionada();

        if (caminho.isEmpty() || idConta <= 0) {
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
                if (campos.size() >= 5) { // É uma boa prática ajustar a verificação para o número correto de campos
                    TransacaoImportada t;
                    t.dataStr = campos[0];
                    t.descricaoStr = campos[1];
                    t.categoriaStr = campos[2];
                    t.valorStr = campos[3];     // Agora receberá "R$ 3,03" corretamente
                    t.tipoStr = campos[4];      // Pega o tipo do campo correto
                    transacoesLidas.append(t);
                }
            }
            file.close();

            // --- FIM DA LÓGICA DE LEITURA ---

            if (transacoesLidas.isEmpty()) {
                QMessageBox::information(this, "Importação", "Nenhuma transação válida encontrada no arquivo.");
                return;
            }

            dialogMapeamento dialogoMap(transacoesLidas, this);
            if (dialogoMap.exec() == QDialog::Accepted)
            {
                // --- ETAPA FINAL: PROCESSAR E SALVAR NO BANCO (VERSÃO FINAL E CORRIGIDA) ---
                QVector<TransacaoImportada> transacoesFinalizadas = dialogoMap.getTransacoesFinalizadas();
                QString token = SessionManager::instance().getToken();
                int sucessoCount = 0;
                int ignoradoCount = 0;
                QLocale brLocale(QLocale::Portuguese, QLocale::Brazil);

                for (const auto& transacaoImportada : transacoesFinalizadas) {
                    if (transacaoImportada.id_categoria <= 0) {
                        ignoradoCount++;
                        continue;
                    }

                    Lancamento novoLancamento;
                    novoLancamento.id_conta = idConta;
                    novoLancamento.id_categoria = transacaoImportada.id_categoria;
                    novoLancamento.id_meta = -1;

                    // Cria cópias locais para modificação segura
                    QString descricaoLimpa = transacaoImportada.descricaoStr;
                    QString dataLimpa = transacaoImportada.dataStr;
                    novoLancamento.descricao = descricaoLimpa.remove('"').trimmed();
                    novoLancamento.data_lancamento = QDate::fromString(dataLimpa.remove('"').trimmed(), "dd/MM/yyyy");
                    QString tipoLimpo = transacaoImportada.tipoStr; // 1. Crie uma cópia local e modificável
                    novoLancamento.tipo = tipoLimpo.remove('"').trimmed(); // 2. Modifique e atribua a cópia

                    // --- LÓGICA DE VALOR CORRIGIDA ---
                    // 1. Limpa a string do valor, removendo tudo exceto dígitos, ponto e vírgula
                    QString valorStr = transacaoImportada.valorStr;
                    valorStr = valorStr.remove(QRegularExpression("[^\\d,.-]")); // Mantém o sinal de menos

                    // 2. Padroniza o separador decimal para PONTO
                    valorStr.replace(',', '.');

                    // 3. Converte a string limpa e padronizada
                    bool ok;
                    double valor = valorStr.toDouble(&ok);

                    if (!ok) {
                        qDebug() << "Falha ao converter o valor '" << transacaoImportada.valorStr << "' -> '" << valorStr << "'";
                        ignoradoCount++;
                        continue;
                    }

                    novoLancamento.valor = valor;
                    novoLancamento.valor_original = valor;
                    // --- FIM DA CORREÇÃO ---

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
        }
        else
        {
            QMessageBox::warning(this, "Arquivo Inválido", "Por favor, selecione um arquivo com formato válido (.csv ou .pdf).");
        }
    }
}

// Adicione o novo slot para lidar com a resposta do OCR
void pageLancamentos::onOcrConcluido(const QVector<TransacaoImportada>& transacoes)
{
    QMessageBox::information(this, "OCR Concluído", "O texto do PDF foi extraído com sucesso! (Verifique o console de depuração). O próximo passo será analisar este texto para encontrar as transações.");

    // No futuro, aqui abriremos o dialogMapeamento com as 'transacoes'
    // dialogMapeamento dialogoMap(transacoes, this);
    // if (dialogoMap.exec() == QDialog::Accepted) { ... }
}