#include "LancamentoDAO.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "Modelo/Conta.h"
#include "Modelo/Categoria.h"
#include <QHttpMultiPart>
#include <QFile>
#include <QFileInfo>
#include "Modelo/TransacaoImportada.h"

LancamentoDAO::LancamentoDAO(QObject *parent)
    : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

// --- ADICIONAR LANÇAMENTO ---
void LancamentoDAO::adicionarLancamento(const Lancamento& lancamento, const QString& token)
{
    QJsonObject json;
    json["descricao"] = lancamento.descricao;
    json["data_lancamento"] = lancamento.data_lancamento.toString(Qt::ISODate);
    json["tipo"] = lancamento.tipo;
    json["id_conta"] = lancamento.id_conta;
    json["id_categoria"] = lancamento.id_categoria;

    // <-- ALTERAÇÃO MÚLTIPLA MOEDA -->
    // Enviamos o valor na moeda principal (convertido) e os dados originais
    json["valor"] = lancamento.valor;
    json["valor_original"] = lancamento.valor_original;
    json["moeda_codigo_original"] = lancamento.moeda_codigo_original;
    json["taxa_cambio_usada"] = lancamento.taxa_cambio_usada;

    if (lancamento.id_meta > 0) {
        json["id_meta"] = lancamento.id_meta;
    }

    QNetworkRequest request(QUrl(m_baseUrl + "/adicionar"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=](){
        if (reply->error() == QNetworkReply::NoError) {
            emit lancamentoAdicionado();
        } else {
            emit onLancamentoError("Falha ao adicionar lançamento: " + reply->errorString() + " | " + reply->readAll());
        }
        reply->deleteLater();
    });
}

void LancamentoDAO::onAdicionarLancamentoReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201) {
        emit lancamentoAdicionado();
    } else {
        emit onLancamentoError("Falha ao adicionar lançamento: " + reply->errorString() + " | " + reply->readAll());
    }
    reply->deleteLater();
}

// --- OBTER TODOS OS LANÇAMENTOS ---
void LancamentoDAO::obterTodos(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta)
{
    QUrl url(m_baseUrl + "/"); // A rota é a raiz dos lançamentos
    QUrlQuery query;
    query.addQueryItem("data_inicio", dataInicio.toString(Qt::ISODate));
    query.addQueryItem("data_fim", dataFim.toString(Qt::ISODate));
    query.addQueryItem("id_conta", QString::number(idConta));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=](){ onObterLancamentosReply(reply); });
}

// --- OBTER LANÇAMENTOS RECENTES ---
void LancamentoDAO::obterRecentes(const QString& token, int limite)
{
    QUrl url(m_baseUrl + "/recentes");
    QUrlQuery query;
    query.addQueryItem("limite", QString::number(limite));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=](){ onObterLancamentosReply(reply); });
}

void LancamentoDAO::onObterLancamentosReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {

        QVector<Lancamento> lista;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            Lancamento l;
            l.id = obj["id"].toInt();
            l.descricao = obj["descricao"].toString();
            l.data_lancamento = QDate::fromString(obj["data_lancamento"].toString().left(10), Qt::ISODate);
            l.tipo = obj["tipo"].toString();
            l.id_usuario = obj["id_usuario"].toInt();
            l.id_conta = obj["id_conta"].toInt();
            l.id_categoria = obj["id_categoria"].toInt();
            l.nome_conta = obj["nome_conta"].toString();
            l.nome_categoria = obj["nome_categoria"].toString();

            // <-- ALTERAÇÃO MÚLTIPLA MOEDA -->
            l.valor = obj["valor"].toDouble();
            l.valor_original = obj["valor_original"].toDouble();
            l.moeda_codigo_original = obj["moeda_codigo_original"].toString();
            l.taxa_cambio_usada = obj["taxa_cambio_usada"].toDouble();

            lista.append(l);
        }
        emit lancamentosRecebidos(lista);
    } else {
        emit onLancamentoError("Falha ao buscar lançamentos: " + reply->errorString() + " | " + reply->readAll());
    }
    reply->deleteLater();
}



void LancamentoDAO::editarLancamento(const Lancamento& lancamento, const QString& token)
{
    QJsonObject json;
    json["descricao"] = lancamento.descricao;
    json["data_lancamento"] = lancamento.data_lancamento.toString(Qt::ISODate);
    json["tipo"] = lancamento.tipo;
    json["id_conta"] = lancamento.id_conta;
    json["id_categoria"] = lancamento.id_categoria;

    // <-- ALTERAÇÃO MÚLTIPLA MOEDA -->
    json["valor"] = lancamento.valor;
    json["valor_original"] = lancamento.valor_original;
    json["moeda_codigo_original"] = lancamento.moeda_codigo_original;
    json["taxa_cambio_usada"] = lancamento.taxa_cambio_usada;

    if (lancamento.id_meta > 0) {
        json["id_meta"] = lancamento.id_meta;
    }

    QNetworkRequest request(QUrl(m_baseUrl + "/" + QString::number(lancamento.id)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->put(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit lancamentoModificadoComSucesso();
        } else {
            emit onLancamentoError("Falha ao editar lançamento: " + reply->errorString() + " | " + reply->readAll());
        }
        reply->deleteLater();
    });
}

void LancamentoDAO::excluirLancamento(int idLancamento, const QString& token)
{
    // A URL agora inclui o ID do lançamento a ser deletado
    QNetworkRequest request(QUrl(m_baseUrl + "/" + QString::number(idLancamento)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit lancamentoExcluidoComSucesso();
        } else {
            emit onLancamentoError("Falha ao excluir lançamento: " + reply->errorString());
        }
        reply->deleteLater();
    });
}


void LancamentoDAO::processarExtratoOcr(const QString& caminhoPdf, const QString& token)
{
    // 1. Cria um objeto "multipart" que irá conter as partes do nosso upload
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // 2. Cria a parte do ficheiro
    QHttpPart filePart;
    QFile *file = new QFile(caminhoPdf);
    if (!file->open(QIODevice::ReadOnly)) {
        emit onLancamentoError("Não foi possível abrir o ficheiro PDF para leitura.");
        delete multiPart;
        delete file;
        return;
    }
    // O backend espera o ficheiro no campo 'extrato'
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"extrato\"; filename=\"%1\"").arg(QFileInfo(caminhoPdf).fileName())));
    filePart.setBodyDevice(file);
    file->setParent(multiPart); // Garante que o ficheiro será fechado e eliminado corretamente

    // 3. Adiciona a parte do ficheiro ao corpo da requisição
    multiPart->append(filePart);

    // 4. Configura e envia a requisição POST
    QUrl url("http://localhost:3000/api/extratos/ocr");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->post(request, multiPart);
    multiPart->setParent(reply);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            // --- INÍCIO DA MUDANÇA ---
            QVector<TransacaoImportada> transacoes;
            QJsonObject obj = QJsonDocument::fromJson(reply->readAll()).object();

            // Lê o array "transacoes" da resposta do backend
            QJsonArray transacoesArray = obj["transacoes"].toArray();

            for (const QJsonValue& val : transacoesArray) {
                QJsonObject tObj = val.toObject();
                TransacaoImportada t;
                t.dataStr = tObj["dataStr"].toString();
                t.descricaoStr = tObj["descricaoStr"].toString();
                t.categoriaStr = tObj["categoriaStr"].toString();
                t.valorStr = tObj["valorStr"].toString();
                t.tipoStr = tObj["tipoStr"].toString();
                transacoes.append(t);
            }

            // Emite o sinal com o vetor de transações prontas
            emit ocrProcessadoComSucesso(transacoes);
            // --- FIM DA MUDANÇA ---

        } else {
            emit onLancamentoError("Falha no processamento OCR: " + reply->readAll());
        }
        reply->deleteLater();
    });
}


void LancamentoDAO::obterSugestoesCategorias(const QVector<QString>& descricoes, const QString& token)
{
    // 1. Monta o corpo JSON que a API espera
    QJsonObject jsonBody;
    QJsonArray jsonArrayDescricoes;
    for (const QString& desc : descricoes) {
        jsonArrayDescricoes.append(desc);
    }
    jsonBody["descricoes"] = jsonArrayDescricoes;

    // 2. Configura a requisição POST
    QNetworkRequest request(QUrl("http://localhost:3000/api/categorias/sugerir"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(jsonBody).toJson());

    // 3. Conecta a resposta ao nosso novo slot
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onSugestoesReply(reply);
    });
}

void LancamentoDAO::onSugestoesReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // 1. Mapa para guardar o resultado: "Descrição da Transação" -> ID da Categoria Sugerida
        QMap<QString, int> mapaDeSugestoes;

        // 2. Processa a resposta JSON do backend
        QJsonObject jsonObj = QJsonDocument::fromJson(reply->readAll()).object();
        QJsonArray sugestoesArray = jsonObj["sugestoes"].toArray();

        for (const QJsonValue& val : sugestoesArray) {
            QJsonObject sugestaoObj = val.toObject();
            QString descricao = sugestaoObj["descricaoOriginal"].toString();
            // Se o ID for nulo no JSON, toInt() retorna 0. Usamos -1 como nosso "não encontrado".
            int idCategoria = sugestaoObj["idCategoriaSugerida"].isNull() ? -1 : sugestaoObj["idCategoriaSugerida"].toInt();

            if (idCategoria > 0) { // Apenas armazena sugestões válidas
                mapaDeSugestoes[descricao] = idCategoria;
            }
        }

        // 3. Emite o sinal com o mapa de sugestões pronto para uso
        emit sugestoesRecebidas(mapaDeSugestoes);

    } else {
        // Em caso de erro, emite o sinal de erro genérico
        emit onLancamentoError("Falha ao buscar sugestões de categorias: " + reply->readAll());
    }
    reply->deleteLater();
}

void LancamentoDAO::obterConnectToken(const QString& token)
{
    QJsonObject jsonBody; // O corpo pode ser vazio para uma nova conexão

    QNetworkRequest request(QUrl("http://localhost:3000/api/openfinance/connect-token"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(jsonBody).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onConnectTokenReply(reply);
    });
}

void LancamentoDAO::onConnectTokenReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject resultado = QJsonDocument::fromJson(reply->readAll()).object();
        emit connectTokenRecebido(resultado["accessToken"].toString());
    } else {
        emit onLancamentoError("Falha ao obter o token de conexão: " + reply->readAll());
    }
    reply->deleteLater();
}

