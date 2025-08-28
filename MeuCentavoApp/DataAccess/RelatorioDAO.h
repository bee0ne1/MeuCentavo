#ifndef RELATORIODAO_H
#define RELATORIODAO_H

#include <QObject>
#include <QVector>
#include <QHash>
#include <QMap>
#include <QDate>

// Forward declarations
class QNetworkAccessManager;
class QNetworkReply;

// Structs e Typedefs movidos para cá
typedef QMap<QString, double> DreData;
typedef QMap<QString, double> FluxoCaixaData;

struct HistoricoPatrimonio { QString mes; double valor; };
struct PontoTendencia { QString mes; double total; };
struct LinhaCronograma { int mes; QString nomeDivida; double valorPago; double saldoRestante; };
struct ResumoMensal { QString mes; double receitas; double despesas; };

class RelatorioDAO : public QObject
{
    Q_OBJECT
public:
    explicit RelatorioDAO(QObject *parent = nullptr);

    // MÉTODOS DE RELATÓRIOS
    void obterResumosDoMes(const QString& token);
    void obterGastosPorCategoria(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta);
    void obterComparativoMensal(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta);
    void obterHistoricoPatrimonio(const QString& token);
    void obterTendenciaCategoria(int idCategoria, const QString& token);
    void obterDre(const QString& token, const QDate& dataInicio, const QDate& dataFim);
    void obterFluxoCaixa(const QString& token, const QDate& dataInicio, const QDate& dataFim);

    // MÉTODOS DE SIMULADORES
    void simularPlanoQuitacao(double valorExtra, const QString& estrategia, const QString& token);
    void simularAposentadoria(int idadeAtual, int idadeAposentadoria, double saldoInicial, double aporteMensal, double rentabilidadeAnual, const QString& token);
    void simularFinanciamento(double valorBem, double valorEntrada, double taxaJurosAnual, int numParcelas, const QString& token);
    void simularCambio(const QString& moedaOrigem, const QString& moedaDestino, double valor, const QString& token);

signals:
    void resumosRecebidos(double receitas, double despesas);
    void gastosPorCategoriaRecebidos(const QHash<QString, double>& dadosGrafico);
    void comparativoMensalRecebido(const QVector<ResumoMensal>& resumo);
    void historicoPatrimonioRecebido(const QVector<HistoricoPatrimonio>& historico);
    void tendenciaCategoriaRecebida(const QVector<PontoTendencia>& tendencia);
    void dreRecebido(const DreData& dre);
    void fluxoCaixaRecebido(const FluxoCaixaData& fluxoCaixa);
    void planoSimuladoRecebido(const QVector<LinhaCronograma>& cronograma, int mesesTotais);
    void simulacaoAposentadoriaRecebida(double valorFinal, double totalInvestido, double jurosTotais);
    void simulacaoFinanciamentoRecebida(double valorParcela, double totalPago, double totalJuros);
    void simulacaoCambioRecebida(double valorConvertido);
    void onRelatorioError(const QString& mensagem);

private slots:
    void onObterResumosReply();
    void onObterGastosCategoriaReply();
    void onObterComparativoMensalReply();
    void onHistoricoPatrimonioReply();
    void onTendenciaCategoriaReply();
    void onDreReply();
    void onFluxoCaixaReply();
    void onPlanoSimuladoReply();
    void onSimulacaoAposentadoriaReply();
    void onSimulacaoFinanciamentoReply();
    void onSimulacaoCambioReply();

private:
    QNetworkAccessManager *m_manager;
    QString m_baseUrl;
};

#endif // RELATORIODAO_H