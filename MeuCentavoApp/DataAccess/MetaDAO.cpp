#include "MetaDAO.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MetaDAO::MetaDAO(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

void MetaDAO::obterTodasMetas(const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/metas"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &MetaDAO::onMetasReply);
}

void MetaDAO::onMetasReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        QVector<Meta> lista;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            Meta m;
            m.id_meta = obj["id_meta"].toInt();
            m.nome = obj["nome"].toString();
            m.valor_alvo = obj["valor_alvo"].toDouble();
            m.valor_atual = obj["valor_atual"].toDouble();
            m.data_alvo = QDate::fromString(obj["data_alvo"].toString().left(10), Qt::ISODate);
            m.moeda_codigo = obj["moeda_codigo"].toString();
            lista.append(m);
        }
        emit metasRecebidas(lista);
    } else {
        emit onMetaError("Falha ao buscar metas: " + reply->errorString() + " | " + reply->readAll());
    }
    reply->deleteLater();
}

void MetaDAO::adicionarMeta(const Meta& meta, const QString& token)
{
    QJsonObject json;
    json["nome"] = meta.nome;
    json["valor_alvo"] = meta.valor_alvo;
    json["moeda_codigo"] = meta.moeda_codigo;
    if (meta.data_alvo.isValid()) {
        json["data_alvo"] = meta.data_alvo.toString(Qt::ISODate);
    }

    QNetworkRequest request(QUrl("http://localhost:3000/api/metas"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &MetaDAO::onModificarMetaReply);
}

void MetaDAO::editarMeta(const Meta& meta, const QString& token)
{
    QJsonObject json;
    json["nome"] = meta.nome;
    json["valor_alvo"] = meta.valor_alvo;
    json["moeda_codigo"] = meta.moeda_codigo;
    if (meta.data_alvo.isValid()) {
        json["data_alvo"] = meta.data_alvo.toString(Qt::ISODate);
    }

    QNetworkRequest request(QUrl("http://localhost:3000/api/metas/" + QString::number(meta.id_meta)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->put(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &MetaDAO::onModificarMetaReply);
}

void MetaDAO::excluirMeta(int idMeta, const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/metas/" + QString::number(idMeta)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &MetaDAO::onModificarMetaReply);
}

void MetaDAO::onModificarMetaReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        emit metaModificadaComSucesso();
    } else {
        emit onMetaError("Falha ao modificar meta: " + reply->readAll());
    }
    reply->deleteLater();
}