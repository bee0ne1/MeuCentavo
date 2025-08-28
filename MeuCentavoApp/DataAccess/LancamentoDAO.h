#ifndef LANCAMENTODAO_H
#define LANCAMENTODAO_H

#include <QObject>
#include <QVector>
#include <QHash>
#include <QMap>
#include "Modelo/Lancamento.h"
#include "Modelo/Conta.h"
#include "Modelo/Categoria.h"
#include "Modelo/Meta.h"
#include "Modelo/TransacaoImportada.h"

// Forward declarations para as classes de rede
class QNetworkAccessManager;
class QNetworkReply;

typedef QMap<QString, double> DreData;
typedef QMap<QString, double> FluxoCaixaData;


class LancamentoDAO : public QObject
{
    Q_OBJECT
public:
    explicit LancamentoDAO(QObject *parent = nullptr);

    // MÉTODOS DE LANÇAMENTOS
    void adicionarLancamento(const Lancamento& lancamento, const QString& token);
    void obterTodos(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta);
    void obterRecentes(const QString& token, int limite = 10);
    void editarLancamento(const Lancamento& lancamento, const QString& token);
    void excluirLancamento(int idLancamento, const QString& token);
    void processarExtratoOcr(const QString& caminhoPdf, const QString& token);


    void obterSugestoesCategorias(const QVector<QString>& descricoes, const QString& token);
    void obterConnectToken(const QString& token);

signals:
    void lancamentoAdicionado();
    void lancamentosRecebidos(const QVector<Lancamento>& lancamentos);
    void lancamentoModificadoComSucesso();
    void lancamentoExcluidoComSucesso();
    void ocrProcessadoComSucesso(const QVector<TransacaoImportada>& transacoes);
    void sugestoesRecebidas(const QMap<QString, int>& mapaDeSugestoes);
    void connectTokenRecebido(const QString& connectToken);
    void onLancamentoError(const QString& mensagem);

private slots:
    void onAdicionarLancamentoReply(QNetworkReply *reply);
    void onObterLancamentosReply(QNetworkReply *reply);
    void onSugestoesReply(QNetworkReply *reply);
    void onConnectTokenReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
    QString m_baseUrl = "http://localhost:3000/api/lancamentos";
};

#endif // LANCAMENTODAO_H