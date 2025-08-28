#ifndef INVESTIMENTODAO_H
#define INVESTIMENTODAO_H

#include <QObject>
#include <QVector>
#include "Modelo/Ativo.h"
#include "Modelo/OperacaoInvestimento.h"
#include "Modelo/Dividendo.h"

// Struct para o resultado da Calculadora de IR
struct ResultadoIR {
    double totalVendas;
    double lucroApurado;
    bool isento;
    double impostoDevido;
};

Q_DECLARE_METATYPE(ResultadoIR)

class QNetworkAccessManager;
class QNetworkReply;

class InvestimentoDAO : public QObject
{
    Q_OBJECT
public:
    explicit InvestimentoDAO(QObject *parent = nullptr);

    // Métodos públicos para a interface chamar
    void obterTodosAtivos(const QString& token);
    void adicionarAtivo(const Ativo& ativo, const QString& token);
    void editarAtivo(const Ativo& ativo, const QString& token);
    void excluirAtivo(int idAtivo, const QString& token);
    void obterOperacoesDeAtivo(int idAtivo, const QString& token);
    void adicionarOperacao(const OperacaoInvestimento& operacao, const QString& token);
    void obterPortfolioConsolidado(const QString& token);
    void obterPerformancePortfolio(const QString& token);
    void adicionarDividendo(const Dividendo& dividendo, const QString& token);
    void obterDividendosDeAtivo(int idAtivo, const QString& token);
    void calcularIRsobreAcoes(int mes, int ano, const QString& token);

signals:
    // Sinais para notificar a interface sobre os resultados
    void ativosRecebidos(const QVector<Ativo>& ativos);
    void ativoModificadoComSucesso();
    void operacoesRecebidas(const QVector<OperacaoInvestimento>& operacoes);
    void operacaoModificadaComSucesso();
    void performancePortfolioRecebida(double custoTotal, double valorMercado, double rentabilidadeValor, double rentabilidadePercentual);
    void dividendoAdicionadoComSucesso();
    void dividendosRecebidos(const QVector<Dividendo>& dividendos);
    void calculoIRRecebido(const ResultadoIR& resultado);
    void onInvestimentoError(const QString& mensagem);

private slots:
    // Slots privados para processar as respostas da rede
    void onAtivosReply(QNetworkReply *reply);
    void onModificarAtivoReply(QNetworkReply *reply);
    void onOperacoesReply(QNetworkReply *reply);
    void onModificarOperacaoReply(QNetworkReply *reply);
    void onDividendosReply(QNetworkReply *reply);
    void onPerformancePortfolioReply(QNetworkReply *reply);
    void onCalculoIRReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
};

#endif // INVESTIMENTODAO_H