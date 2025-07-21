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
    json["valor"] = lancamento.valor;
    json["data_lancamento"] = lancamento.data_lancamento.toString(Qt::ISODate);
    json["tipo"] = lancamento.tipo;
    json["id_conta"] = lancamento.id_conta;
    json["id_categoria"] = lancamento.id_categoria;

    QNetworkRequest request(QUrl(m_baseUrl + "/adicionar"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=](){
        onAdicionarLancamentoReply(reply);
    });
}

void LancamentoDAO::onAdicionarLancamentoReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201) {
        emit lancamentoAdicionado();
    } else {
        emit erroOcorrido("Falha ao adicionar lançamento: " + reply->errorString() + " | " + reply->readAll());
    }
    reply->deleteLater();
}

// --- OBTER TODOS OS LANÇAMENTOS ---
void LancamentoDAO::obterTodos(const QString& token)
{
    QNetworkRequest request(QUrl(m_baseUrl + "/"));
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
            l.valor = obj["valor"].toDouble();
            l.data_lancamento = QDate::fromString(obj["data_lancamento"].toString().left(10), Qt::ISODate);
            l.tipo = obj["tipo"].toString();
            l.id_usuario = obj["id_usuario"].toInt();
            lista.append(l);
        }
        emit lancamentosRecebidos(lista);
    } else {
        emit erroOcorrido("Falha ao buscar lançamentos: " + reply->errorString());
    }
    reply->deleteLater();
}

// --- OBTER RESUMOS DO MÊS ---
void LancamentoDAO::obterResumosDoMes(const QString& token)
{
    QNetworkRequest request(QUrl(m_baseUrl + "/resumo/mes"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=](){ onObterResumosReply(reply); });
}

void LancamentoDAO::onObterResumosReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        QJsonObject jsonObj = QJsonDocument::fromJson(reply->readAll()).object();
        double receitas = jsonObj["receitas"].toDouble();
        double despesas = jsonObj["despesas"].toDouble();
        emit resumosRecebidos(receitas, despesas);
    } else {
        emit erroOcorrido("Falha ao buscar resumos: " + reply->errorString());
    }
    reply->deleteLater();
}

// --- OBTER GASTOS POR CATEGORIA (PARA O GRÁFICO) ---
void LancamentoDAO::obterGastosPorCategoria(const QString& token)
{
    // Este método dependerá de uma rota como GET /api/lancamentos/gastos/categoria
    // A implementação seguirá o mesmo padrão das outras funções GET.
    // O slot onObterGastosCategoriaReply irá processar a resposta e emitir
    // o sinal gastosPorCategoriaRecebidos(dadosDoGrafico).
}

void LancamentoDAO::onObterGastosCategoriaReply(QNetworkReply *reply)
{
    // Implementação futura, similar a onObterLancamentosReply
    reply->deleteLater();
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
            emit erroOcorrido("Falha ao excluir lançamento: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void LancamentoDAO::obterTodasContas(const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/contas"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=](){ onObterContasReply(reply); });
}

void LancamentoDAO::onObterContasReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QVector<Conta> lista;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            Conta c;
            c.id = obj["id_conta"].toInt();
            c.nome = obj["nome"].toString();
            // Preencha outros campos se necessário
            lista.append(c);
        }
        emit contasRecebidas(lista);
    } else {
        emit erroOcorrido("Falha ao buscar contas: " + reply->errorString());
    }
    reply->deleteLater();
}

void LancamentoDAO::obterTodasCategorias(const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/categorias"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() { onObterCategoriasReply(reply); });
}

void LancamentoDAO::onObterCategoriasReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QVector<Categoria> lista;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            Categoria c;
            c.id = obj["id_categoria"].toInt();
            c.nome = obj["nome"].toString();

            // --- PONTO CRÍTICO DA CORREÇÃO ---
            // Esta linha garante que estamos a ler a chave "tipo" (minúsculas),
            // que corresponde ao nome da sua coluna no banco de dados.
            c.tipo = obj["tipo"].toString();

            // --- LINHA DE DEBUG PARA CONFIRMAR ---
            qDebug() << "DAO PARSING -> Nome:" << c.nome << "| Tipo Lido do JSON:" << "'" + c.tipo + "'";

            // Preencha outros campos se necessário
            lista.append(c);
        }
        emit categoriasRecebidas(lista);
    } else {
        emit erroOcorrido("Falha ao buscar categorias: " + reply->errorString());
    }
    reply->deleteLater();
}

void LancamentoDAO::adicionarCategoria(const Categoria& categoria, const QString& token)
{
    QJsonObject json;
    json["nome"] = categoria.nome;
    json["tipo"] = categoria.tipo;

    QNetworkRequest request(QUrl("http://localhost:3000/api/categorias"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() { onModificarCategoriaReply(reply); });
}

void LancamentoDAO::editarCategoria(int idCategoria, const QString& novoNome, const QString& token)
{
    QJsonObject json;
    json["nome"] = novoNome;

    QNetworkRequest request(QUrl("http://localhost:3000/api/categorias/" + QString::number(idCategoria)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Usamos o método PUT para edições
    QNetworkReply *reply = m_manager->put(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() { onModificarCategoriaReply(reply); });
}

void LancamentoDAO::excluirCategoria(int idCategoria, const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/categorias/" + QString::number(idCategoria)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, [=]() { onModificarCategoriaReply(reply); });
}

void LancamentoDAO::onModificarCategoriaReply(QNetworkReply *reply)
{
    // Verifica se a operação foi bem-sucedida (status 200 para OK, 201 para Criado)
    if (reply->error() == QNetworkReply::NoError) {
        emit categoriaModificadaComSucesso();
    } else {
        emit erroOcorrido("Falha ao modificar categoria: " + reply->errorString());
    }
    reply->deleteLater();
}