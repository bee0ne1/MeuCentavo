#include "InvestimentoDAO.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>


InvestimentoDAO::InvestimentoDAO(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

// --- MÉTODOS PARA GESTÃO DE ATIVOS ---

void InvestimentoDAO::obterTodosAtivos(const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/ativos"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=](){ onAtivosReply(reply); });
}

void InvestimentoDAO::onAtivosReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QVector<Ativo> lista;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            Ativo a;
            a.id_ativo = obj["id_ativo"].toInt();
            a.ticker = obj["ticker"].toString();
            a.nome = obj["nome"].toString();
            a.tipo_ativo = obj["tipo_ativo"].toString();
            a.moeda_codigo = obj["moeda_codigo"].toString();
            a.quantidade_total = obj["quantidade_total"].toDouble();
            a.custo_total = obj["custo_total"].toDouble();
            lista.append(a);
        }
        emit ativosRecebidos(lista);
    } else {
        emit onInvestimentoError("Falha ao buscar ativos: " + reply->errorString() + " | " + reply->readAll());
    }
    reply->deleteLater();
}

void InvestimentoDAO::adicionarAtivo(const Ativo& ativo, const QString& token)
{
    QJsonObject json;
    json["ticker"] = ativo.ticker;
    json["nome"] = ativo.nome;
    json["tipo_ativo"] = ativo.tipo_ativo;
    json["moeda_codigo"] = ativo.moeda_codigo;

    QNetworkRequest request(QUrl("http://localhost:3000/api/ativos"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() { onModificarAtivoReply(reply); });
}

void InvestimentoDAO::editarAtivo(const Ativo& ativo, const QString& token)
{
    QJsonObject json;
    json["nome"] = ativo.nome;
    json["tipo_ativo"] = ativo.tipo_ativo;
    json["moeda_codigo"] = ativo.moeda_codigo;

    QNetworkRequest request(QUrl("http://localhost:3000/api/ativos/" + QString::number(ativo.id_ativo)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_manager->put(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() { onModificarAtivoReply(reply); });
}

void InvestimentoDAO::excluirAtivo(int idAtivo, const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/ativos/" + QString::number(idAtivo)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, [=](){ onModificarAtivoReply(reply); });
}

void InvestimentoDAO::onModificarAtivoReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        emit ativoModificadoComSucesso();
    } else {
        emit onInvestimentoError("Falha ao modificar ativo: " + reply->readAll());
    }
    reply->deleteLater();
}

void InvestimentoDAO::obterOperacoesDeAtivo(int idAtivo, const QString& token)
{
    QNetworkRequest request(QUrl(QString("http://localhost:3000/api/ativos/%1/operacoes").arg(idAtivo)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=](){ onOperacoesReply(reply); });
}

void InvestimentoDAO::adicionarOperacao(const OperacaoInvestimento& operacao, const QString& token)
{
    QJsonObject json;
    json["id_ativo"] = operacao.id_ativo;
    json["tipo_operacao"] = operacao.tipo_operacao;
    json["data_operacao"] = operacao.data_operacao.toString(Qt::ISODate);
    json["quantidade"] = operacao.quantidade;
    json["preco_unitario"] = operacao.preco_unitario;
    json["custos"] = operacao.custos;
    json["moeda_codigo"] = operacao.moeda_codigo;
    json["taxa_cambio_usada"] = operacao.taxa_cambio_usada;

    QNetworkRequest request(QUrl("http://localhost:3000/api/operacoes"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() { onModificarOperacaoReply(reply); });
}

void InvestimentoDAO::onOperacoesReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QVector<OperacaoInvestimento> lista;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            OperacaoInvestimento o;
            o.id_operacao = obj["id_operacao"].toInt();
            o.id_ativo = obj["id_ativo"].toInt();
            o.tipo_operacao = obj["tipo_operacao"].toString();
            o.data_operacao = QDate::fromString(obj["data_operacao"].toString().left(10), Qt::ISODate);
            o.quantidade = obj["quantidade"].toDouble();
            o.preco_unitario = obj["preco_unitario"].toDouble();
            o.custos = obj["custos"].toDouble();
            o.moeda_codigo = obj["moeda_codigo"].toString();
            o.taxa_cambio_usada = obj["taxa_cambio_usada"].toDouble();
            lista.append(o);
        }
        emit operacoesRecebidas(lista);
    } else {
        emit onInvestimentoError("Falha ao buscar operações: " + reply->errorString() + " | " + reply->readAll());
    }
    reply->deleteLater();
}

void InvestimentoDAO::onModificarOperacaoReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        emit operacaoModificadaComSucesso();
    } else {
        emit onInvestimentoError("Falha ao modificar operação: " + reply->readAll());
    }
    reply->deleteLater();
}

void InvestimentoDAO::obterPortfolioConsolidado(const QString& token)
{
    QNetworkRequest request{QUrl("http://localhost:3000/api/ativos/portfolio")};
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=](){ onAtivosReply(reply); });
}

void InvestimentoDAO::obterPerformancePortfolio(const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/portfolio/performance"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() { onPerformancePortfolioReply(reply); });
}

void InvestimentoDAO::onPerformancePortfolioReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject obj = QJsonDocument::fromJson(reply->readAll()).object();
        emit performancePortfolioRecebida(
            obj["custoTotal"].toDouble(),
            obj["valorMercadoAtual"].toDouble(),
            obj["rentabilidadeValor"].toDouble(),
            obj["rentabilidadePercentual"].toDouble()
        );
    } else {
        emit onInvestimentoError("Falha ao buscar performance do portfólio: " + reply->errorString());
    }
    reply->deleteLater();
}

void InvestimentoDAO::adicionarDividendo(const Dividendo& dividendo, const QString& token) {
    QJsonObject json;
    json["id_ativo"] = dividendo.id_ativo;
    json["data_pagamento"] = dividendo.data_pagamento.toString(Qt::ISODate);
    json["valor_total"] = dividendo.valor_total;

    QNetworkRequest request(QUrl("http://localhost:3000/api/dividendos"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=](){
         if (reply->error() == QNetworkReply::NoError) {
            emit dividendoAdicionadoComSucesso();
         } else {
            emit onInvestimentoError("Falha ao registrar dividendo: " + reply->readAll());
         }
         reply->deleteLater();
    });
}

void InvestimentoDAO::obterDividendosDeAtivo(int idAtivo, const QString& token)
{
    QNetworkRequest request(QUrl(QString("http://localhost:3000/api/ativos/%1/dividendos").arg(idAtivo)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() { onDividendosReply(reply); });
}

void InvestimentoDAO::onDividendosReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QVector<Dividendo> lista;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            Dividendo d;
            d.id_dividendo = obj["id_dividendo"].toInt();
            d.id_ativo = obj["id_ativo"].toInt();
            d.id_usuario = obj["id_usuario"].toInt();
            d.data_pagamento = QDate::fromString(obj["data_pagamento"].toString().left(10), Qt::ISODate);
            d.valor_total = obj["valor_total"].toDouble();
            lista.append(d);
        }
        emit dividendosRecebidos(lista);
    } else {
        emit onInvestimentoError("Falha ao buscar dividendos: " + reply->readAll());
    }
    reply->deleteLater();
}

void InvestimentoDAO::calcularIRsobreAcoes(int mes, int ano, const QString& token)
{
    QUrl url("http://localhost:3000/api/impostos/acoes");
    QUrlQuery query;
    query.addQueryItem("mes", QString::number(mes));
    query.addQueryItem("ano", QString::number(ano));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() { onCalculoIRReply(reply); });
}

void InvestimentoDAO::onCalculoIRReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject obj = QJsonDocument::fromJson(reply->readAll()).object();
        ResultadoIR res;
        res.totalVendas = obj["totalVendasNoMes"].toDouble();
        res.lucroApurado = obj["lucroApurado"].toDouble();
        res.isento = obj["isento"].toBool();
        res.impostoDevido = obj["impostoDevido"].toDouble();
        emit calculoIRRecebido(res);
    } else {
        emit onInvestimentoError("Falha ao calcular IR: " + reply->readAll());
    }
    reply->deleteLater();
}