#include "RelatorioDAO.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

RelatorioDAO::RelatorioDAO(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
    m_baseUrl = "http://localhost:3000/api/lancamentos";
}


void RelatorioDAO::obterResumosDoMes(const QString& token)
{
    QNetworkRequest request(QUrl(m_baseUrl + "/resumo/mes"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=](){ onObterResumosReply(); });
}

void RelatorioDAO::onObterResumosReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        QJsonObject jsonObj = QJsonDocument::fromJson(reply->readAll()).object();
        double receitas = jsonObj["receitas"].toDouble();
        double despesas = jsonObj["despesas"].toDouble();
        emit resumosRecebidos(receitas, despesas);
    } else {
        emit onRelatorioError("Falha ao buscar resumos: " + reply->errorString());
    }
    reply->deleteLater();
}

// --- OBTER GASTOS POR CATEGORIA (PARA O GRÁFICO) ---
void RelatorioDAO::obterGastosPorCategoria(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta)
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
    connect(reply, &QNetworkReply::finished, this, [=](){ onObterGastosCategoriaReply(); });
}

void RelatorioDAO::onObterGastosCategoriaReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

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
        emit onRelatorioError("Falha ao buscar gastos por categoria: " + reply->errorString());
    }
    reply->deleteLater();
}

void RelatorioDAO::obterComparativoMensal(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta)
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
        onObterComparativoMensalReply();
    });
}

void RelatorioDAO::onObterComparativoMensalReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

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
        emit onRelatorioError("Falha ao buscar comparativo mensal: " + reply->errorString());
    }
    reply->deleteLater();
}

void RelatorioDAO::obterHistoricoPatrimonio(const QString& token)
{
    QNetworkRequest request(QUrl("http://localhost:3000/api/patrimonio/historico"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &RelatorioDAO::onHistoricoPatrimonioReply);
}

void RelatorioDAO::onHistoricoPatrimonioReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        QVector<HistoricoPatrimonio> historico;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            historico.append({obj["mes"].toString(), obj["patrimonio"].toDouble()});
        }
        emit historicoPatrimonioRecebido(historico);
    } else {
        emit onRelatorioError("Falha ao buscar histórico de patrimônio: " + reply->readAll());
    }
    reply->deleteLater();
}

void RelatorioDAO::obterTendenciaCategoria(int idCategoria, const QString& token)
{
    QUrl url("http://localhost:3000/api/relatorios/tendencia-categoria");
    QUrlQuery query;
    query.addQueryItem("id_categoria", QString::number(idCategoria));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &RelatorioDAO::onTendenciaCategoriaReply);
}

void RelatorioDAO::onTendenciaCategoriaReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido
    if (reply->error() == QNetworkReply::NoError) {
        QVector<PontoTendencia> tendencia;
        QJsonArray jsonArray = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            tendencia.append({obj["mes"].toString(), obj["total_gasto"].toDouble()});
        }
        emit tendenciaCategoriaRecebida(tendencia);
    } else {
        emit onRelatorioError("Falha ao buscar tendência da categoria: " + reply->readAll());
    }
    reply->deleteLater();
}

void RelatorioDAO::simularPlanoQuitacao(double valorExtra, const QString& estrategia, const QString& token)
{
    QJsonObject jsonBody;
    jsonBody["valorExtraMensal"] = valorExtra;
    jsonBody["estrategia"] = estrategia;

    QNetworkRequest request(QUrl("http://localhost:3000/api/dividas/simular-plano"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(jsonBody).toJson());

    // Conectamos a resposta ao nosso novo slot de processamento
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onPlanoSimuladoReply();
    });
}

void RelatorioDAO::onPlanoSimuladoReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido
    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject resultadoJson = QJsonDocument::fromJson(reply->readAll()).object();

        QJsonArray cronogramaArray = resultadoJson["cronograma"].toArray();
        int mesesTotais = resultadoJson["mesesTotais"].toInt();
        QVector<LinhaCronograma> cronogramaProcessado;

        for (const QJsonValue& mesValue : cronogramaArray) {
            QJsonObject mesObj = mesValue.toObject();
            int mesAtual = mesObj["mes"].toInt();

            QJsonArray pagamentosArray = mesObj["pagamentos"].toArray();
            for (const QJsonValue& pagValue : pagamentosArray) {
                QJsonObject pagObj = pagValue.toObject();

                LinhaCronograma linha;
                linha.mes = mesAtual;
                linha.nomeDivida = pagObj["nome"].toString();
                linha.valorPago = pagObj["valorPago"].toDouble();
                linha.saldoRestante = pagObj["saldoRestante"].toDouble();

                cronogramaProcessado.append(linha);
            }
        }

        // Emitimos o sinal com os dados já "traduzidos" para C++
        emit planoSimuladoRecebido(cronogramaProcessado, mesesTotais);

    } else {
        emit onRelatorioError("Falha ao simular plano: " + reply->readAll());
    }
    reply->deleteLater();
}


void RelatorioDAO::obterDre(const QString& token, const QDate& dataInicio, const QDate& dataFim)
{
    QUrl url("http://localhost:3000/api/relatorios/dre");
    QUrlQuery query;
    query.addQueryItem("data_inicio", dataInicio.toString(Qt::ISODate));
    query.addQueryItem("data_fim", dataFim.toString(Qt::ISODate));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &RelatorioDAO::onDreReply);
}

void RelatorioDAO::onDreReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject obj = QJsonDocument::fromJson(reply->readAll()).object();
        DreData dre;
        for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
            dre[it.key()] = it.value().toDouble();
        }
        emit dreRecebido(dre);
    } else {
        emit onRelatorioError("Falha ao buscar DRE: " + reply->readAll());
    }
    reply->deleteLater();
}

void RelatorioDAO::obterFluxoCaixa(const QString& token, const QDate& dataInicio, const QDate& dataFim)
{
    QUrl url("http://localhost:3000/api/relatorios/fluxo-caixa");
    QUrlQuery query;
    query.addQueryItem("data_inicio", dataInicio.toString(Qt::ISODate));
    query.addQueryItem("data_fim", dataFim.toString(Qt::ISODate));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &RelatorioDAO::onFluxoCaixaReply);
}

void RelatorioDAO::onFluxoCaixaReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido
    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject obj = QJsonDocument::fromJson(reply->readAll()).object();
        FluxoCaixaData fluxoCaixa;
        for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
            fluxoCaixa[it.key()] = it.value().toDouble();
        }
        emit fluxoCaixaRecebido(fluxoCaixa);
    } else {
        // A resposta original continha um readAll() extra que consumia o corpo da resposta
        emit onRelatorioError("Falha ao buscar Fluxo de Caixa: " + reply->errorString() + " | " + reply->readAll());
    }
    reply->deleteLater();
}

void RelatorioDAO::simularAposentadoria(int idadeAtual, int idadeAposentadoria, double saldoInicial, double aporteMensal, double rentabilidadeAnual, const QString& token)
{
    QJsonObject jsonBody;
    jsonBody["idadeAtual"] = idadeAtual;
    jsonBody["idadeAposentadoria"] = idadeAposentadoria;
    jsonBody["saldoInicial"] = saldoInicial;
    jsonBody["aporteMensal"] = aporteMensal;
    jsonBody["rentabilidadeAnual"] = rentabilidadeAnual;

    QNetworkRequest request(QUrl("http://localhost:3000/api/simuladores/aposentadoria"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(jsonBody).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        onSimulacaoAposentadoriaReply();
    });
}

void RelatorioDAO::onSimulacaoAposentadoriaReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject resultado = QJsonDocument::fromJson(reply->readAll()).object();
        emit simulacaoAposentadoriaRecebida(
            resultado["valorFinal"].toDouble(),
            resultado["totalInvestido"].toDouble(),
            resultado["jurosTotais"].toDouble()
        );
    } else {
        emit onRelatorioError("Falha ao simular aposentadoria: " + reply->readAll());
    }
    reply->deleteLater();
}

void RelatorioDAO::simularFinanciamento(double valorBem, double valorEntrada, double taxaJurosAnual, int numParcelas, const QString& token)
{
    QJsonObject jsonBody;
    jsonBody["valorBem"] = valorBem;
    jsonBody["valorEntrada"] = valorEntrada;
    jsonBody["taxaJurosAnual"] = taxaJurosAnual;
    jsonBody["numParcelas"] = numParcelas;

    QNetworkRequest request(QUrl("http://localhost:3000/api/simuladores/financiamento"));
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(jsonBody).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        onSimulacaoFinanciamentoReply();
    });
}

void RelatorioDAO::onSimulacaoFinanciamentoReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject resultado = QJsonDocument::fromJson(reply->readAll()).object();
        emit simulacaoFinanciamentoRecebida(
            resultado["valorParcela"].toDouble(),
            resultado["totalPago"].toDouble(),
            resultado["totalJuros"].toDouble()
        );
    } else {
        emit onRelatorioError("Falha ao simular financiamento: " + reply->readAll());
    }
    reply->deleteLater();
}

void RelatorioDAO::simularCambio(const QString& moedaOrigem, const QString& moedaDestino, double valor, const QString& token)
{
    QUrl url("http://localhost:3000/api/simuladores/cambio");
    QUrlQuery query;
    query.addQueryItem("from", moedaOrigem);
    query.addQueryItem("to", moedaDestino);
    query.addQueryItem("amount", QString::number(valor));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onSimulacaoCambioReply();
    });
}

void RelatorioDAO::onSimulacaoCambioReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return; // Segurança: Garante que o remetente é válido

    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject resultado = QJsonDocument::fromJson(reply->readAll()).object();
        emit simulacaoCambioRecebida(resultado["valorConvertido"].toDouble());
    } else {
        emit onRelatorioError("Falha ao simular câmbio: " + reply->readAll());
    }
    reply->deleteLater();
}


