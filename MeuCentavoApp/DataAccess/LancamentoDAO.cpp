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

    // Apenas inclui o id_meta no JSON se ele for válido (>0)
    if (lancamento.id_meta > 0) {
        json["id_meta"] = lancamento.id_meta;
    }

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
            l.valor = obj["valor"].toDouble();
            l.data_lancamento = QDate::fromString(obj["data_lancamento"].toString().left(10), Qt::ISODate);
            l.tipo = obj["tipo"].toString();
            l.id_usuario = obj["id_usuario"].toInt();
            l.nome_conta = obj["nome_conta"].toString();
            l.nome_categoria = obj["nome_categoria"].toString();
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
void LancamentoDAO::obterGastosPorCategoria(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta)
{
    // A URL base continua a mesma
    QUrl url(m_baseUrl + "/gastos/categoria");

    // Usamos QUrlQuery para adicionar os parâmetros de forma segura
    QUrlQuery query;
    query.addQueryItem("data_inicio", dataInicio.toString(Qt::ISODate));
    query.addQueryItem("data_fim", dataFim.toString(Qt::ISODate));
    // O id -1 será ignorado pelo backend, representando "todas as contas"
    query.addQueryItem("id_conta", QString::number(idConta));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=](){ onObterGastosCategoriaReply(reply); });
}

void LancamentoDAO::onObterGastosCategoriaReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        QHash<QString, double> dadosGrafico;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            QString nomeCategoria = obj["nome"].toString();
            double total = obj["total"].toDouble();
            dadosGrafico[nomeCategoria] = total;
        }
        emit gastosPorCategoriaRecebidos(dadosGrafico);
    } else {
        emit erroOcorrido("Falha ao buscar gastos por categoria: " + reply->errorString());
    }
    reply->deleteLater();
}

void LancamentoDAO::editarLancamento(const Lancamento& lancamento, const QString& token)
{
    QJsonObject json;
    json["descricao"] = lancamento.descricao;
    json["valor"] = lancamento.valor;
    json["data_lancamento"] = lancamento.data_lancamento.toString(Qt::ISODate);
    json["tipo"] = lancamento.tipo;
    json["id_conta"] = lancamento.id_conta;
    json["id_categoria"] = lancamento.id_categoria;

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
            emit erroOcorrido("Falha ao editar lançamento: " + reply->errorString());
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

// --- MÉTODOS PARA GESTÃO DE CONTAS ---

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

            // Adicionamos as duas linhas que faltavam para ler o tipo e o saldo.
            // Os nomes das chaves ("tipo_conta", "saldo_inicial") devem corresponder
            // exatamente aos nomes das colunas na sua tabela 'contas'.
            c.tipo_conta = obj["tipo_conta"].toString();
            c.saldo_inicial = obj["saldo_inicial"].toDouble();

            // Preencha outros campos se necessário
            lista.append(c);
        }
        emit contasRecebidas(lista);
    } else {
        emit erroOcorrido("Falha ao buscar contas: " + reply->errorString());
    }
    reply->deleteLater();
}


void LancamentoDAO::adicionarConta(const Conta& conta, const QString& token)
{
    QJsonObject json;
    json["nome"] = conta.nome;
    json["tipo_conta"] = conta.tipo_conta;
    json["saldo_inicial"] = conta.saldo_inicial;

    QNetworkRequest request(QUrl("http://localhost:3000/api/contas"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit contaModificadaComSucesso();
        } else {
            emit erroOcorrido("Falha ao adicionar conta: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void LancamentoDAO::editarConta(const Conta& conta, const QString& token)
{
    QJsonObject json;
    json["nome"] = conta.nome;
    json["tipo_conta"] = conta.tipo_conta;
    json["saldo_inicial"] = conta.saldo_inicial;

    QNetworkRequest request(QUrl("http://localhost:3000/api/contas/" + QString::number(conta.id)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->put(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit contaModificadaComSucesso();
        } else {
            emit erroOcorrido("Falha ao editar conta: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void LancamentoDAO::excluirConta(int idConta, const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/contas/" + QString::number(idConta)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit contaModificadaComSucesso();
        } else {
            emit erroOcorrido("Falha ao excluir conta: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void LancamentoDAO::obterComparativoMensal(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta)
{
    QUrl url(m_baseUrl + "/comparativo/mensal"); // Nova rota
    QUrlQuery query;
    query.addQueryItem("data_inicio", dataInicio.toString(Qt::ISODate));
    query.addQueryItem("data_fim", dataFim.toString(Qt::ISODate));
    query.addQueryItem("id_conta", QString::number(idConta));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onObterComparativoMensalReply(reply);
    });
}

void LancamentoDAO::onObterComparativoMensalReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QVector<ResumoMensal> lista;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            ResumoMensal r;
            r.mes = obj["mes"].toString();
            r.receitas = obj["receitas"].toDouble();
            r.despesas = obj["despesas"].toDouble();
            lista.append(r);
        }
        emit comparativoMensalRecebido(lista);
    } else {
        emit erroOcorrido("Falha ao buscar comparativo mensal: " + reply->errorString());
    }
    reply->deleteLater();
}

// --- MÉTODOS PARA GESTÃO DE METAS ---

void LancamentoDAO::obterTodasMetas(const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/metas"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onMetasReply(reply);
    });
}

void LancamentoDAO::onMetasReply(QNetworkReply *reply)
{
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
            lista.append(m);
        }
        emit metasRecebidas(lista);
    } else {
        emit erroOcorrido("Falha ao buscar metas: " + reply->errorString());
    }
    reply->deleteLater();
}

void LancamentoDAO::adicionarMeta(const Meta& meta, const QString& token)
{
    QJsonObject json;
    json["nome"] = meta.nome;
    json["valor_alvo"] = meta.valor_alvo;
    if (meta.data_alvo.isValid()) {
        json["data_alvo"] = meta.data_alvo.toString(Qt::ISODate);
    }

    QNetworkRequest request(QUrl("http://localhost:3000/api/metas"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onModificarMetaReply(reply);
    });
}

void LancamentoDAO::editarMeta(const Meta& meta, const QString& token)
{
    QJsonObject json;
    json["nome"] = meta.nome;
    json["valor_alvo"] = meta.valor_alvo;
    json["valor_atual"] = meta.valor_atual;
    if (meta.data_alvo.isValid()) {
        json["data_alvo"] = meta.data_alvo.toString(Qt::ISODate);
    }

    QNetworkRequest request(QUrl("http://localhost:3000/api/metas/" + QString::number(meta.id_meta)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->put(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onModificarMetaReply(reply);
    });
}

void LancamentoDAO::excluirMeta(int idMeta, const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/metas/" + QString::number(idMeta)));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onModificarMetaReply(reply);
    });
}

void LancamentoDAO::onModificarMetaReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        emit metaModificadaComSucesso();
    } else {
        emit erroOcorrido("Falha ao modificar meta: " + reply->readAll());
    }
    reply->deleteLater();
}
