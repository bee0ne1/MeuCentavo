#include "ContaDAO.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

ContaDAO::ContaDAO(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

// --- MÉTODOS PARA GESTÃO DE CONTAS ---

void ContaDAO::obterTodasContas(const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/contas"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ContaDAO::onObterContasReply);
}

void ContaDAO::onObterContasReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        QVector<Conta> lista;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            Conta c;
            c.id = obj["id_conta"].toInt();
            c.nome = obj["nome"].toString();
            c.tipo_conta = obj["tipo_conta"].toString();
            c.saldo_inicial = obj["saldo_inicial"].toDouble();
            c.id_usuario = obj["id_usuario"].toInt();
            c.moeda_codigo = obj["moeda_codigo"].toString();
            c.taxa_juros = obj["taxa_juros"].toDouble();
            c.valor_total_divida = obj["valor_total_divida"].toDouble();
            if (obj.contains("data_vencimento") && !obj["data_vencimento"].isNull()) {
                c.data_vencimento = QDate::fromString(obj["data_vencimento"].toString().left(10), Qt::ISODate);
            }
            lista.append(c);
        }
        emit contasRecebidas(lista);
    } else {
        emit onContaError("Falha ao buscar contas: " + reply->errorString() + " | " + reply->readAll());
    }
    reply->deleteLater();
}

void ContaDAO::adicionarConta(const Conta& conta, const QString& token)
{
    QJsonObject json;
    json["nome"] = conta.nome;
    json["tipo_conta"] = conta.tipo_conta;
    json["saldo_inicial"] = conta.saldo_inicial;
    json["moeda_codigo"] = conta.moeda_codigo;

    if (conta.valor_total_divida > 0) {
        json["taxa_juros"] = conta.taxa_juros;
        json["valor_total_divida"] = conta.valor_total_divida;
        if (conta.data_vencimento.isValid()) {
            json["data_vencimento"] = conta.data_vencimento.toString(Qt::ISODate);
        }
    }

    QNetworkRequest request(QUrl("http://localhost:3000/api/contas"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &ContaDAO::onModificarContaReply);
}

void ContaDAO::editarConta(const Conta& conta, const QString& token)
{
    QJsonObject json;
    json["nome"] = conta.nome;
    json["tipo_conta"] = conta.tipo_conta;
    json["saldo_inicial"] = conta.saldo_inicial;
    json["moeda_codigo"] = conta.moeda_codigo;

    if (conta.tipo_conta == "Financiamento" || conta.tipo_conta == "Empréstimo" || conta.tipo_conta == "Cartão de Crédito") {
        json["taxa_juros"] = conta.taxa_juros;
        json["valor_total_divida"] = conta.valor_total_divida;
        if (conta.data_vencimento.isValid()) {
            json["data_vencimento"] = conta.data_vencimento.toString(Qt::ISODate);
        }
    }
    
    QNetworkRequest request(QUrl("http://localhost:3000/api/contas/" + QString::number(conta.id)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->put(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &ContaDAO::onModificarContaReply);
}

void ContaDAO::excluirConta(int idConta, const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/contas/" + QString::number(idConta)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &ContaDAO::onModificarContaReply);
}

void ContaDAO::onModificarContaReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        emit contaModificadaComSucesso();
    } else {
        emit onContaError("Falha ao modificar conta: " + reply->errorString() + " | " + reply->readAll());
    }
    reply->deleteLater();
}

// --- MÉTODOS PARA GESTÃO DE CATEGORIAS ---

void ContaDAO::obterTodasCategorias(const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/categorias"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ContaDAO::onObterCategoriasReply);
}

void ContaDAO::onObterCategoriasReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        QVector<Categoria> lista;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            Categoria c;
            c.id = obj["id_categoria"].toInt();
            c.nome = obj["nome"].toString();
            c.tipo = obj["tipo"].toString();
            c.classificacao_contabil = obj["classificacao_contabil"].toString();
            lista.append(c);
        }
        emit categoriasRecebidas(lista);
    } else {
        emit onContaError("Falha ao buscar categorias: " + reply->errorString());
    }
    reply->deleteLater();
}

void ContaDAO::adicionarCategoria(const Categoria& categoria, const QString& token)
{
    QJsonObject json;
    json["nome"] = categoria.nome;
    json["tipo"] = categoria.tipo;
    json["classificacao_contabil"] = categoria.classificacao_contabil;

    QNetworkRequest request(QUrl("http://localhost:3000/api/categorias"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &ContaDAO::onModificarCategoriaReply);
}

void ContaDAO::editarCategoria(const Categoria& categoria, const QString& token)
{
    QJsonObject json;
    json["nome"] = categoria.nome;
    json["classificacao_contabil"] = categoria.classificacao_contabil;

    QNetworkRequest request(QUrl("http://localhost:3000/api/categorias/" + QString::number(categoria.id)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    QNetworkReply *reply = m_manager->put(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &ContaDAO::onModificarCategoriaReply);
}

void ContaDAO::excluirCategoria(int idCategoria, const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/categorias/" + QString::number(idCategoria)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &ContaDAO::onModificarCategoriaReply);
}

void ContaDAO::onModificarCategoriaReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        emit categoriaModificadaComSucesso();
    } else {
        emit onContaError("Falha ao modificar categoria: " + reply->errorString());
    }
    reply->deleteLater();
}