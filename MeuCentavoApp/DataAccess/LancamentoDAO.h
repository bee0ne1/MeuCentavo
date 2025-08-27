#ifndef LANCAMENTODAO_H
#define LANCAMENTODAO_H

#include <QObject>
#include <QVector>
#include <QHash>
#include "Modelo/Lancamento.h"
#include "Modelo/Conta.h" // Crie estes ficheiros de modelo se necessário
#include "Modelo/Categoria.h"
#include "Modelo/OperacaoInvestimento.h"
#include "Modelo/Meta.h"
#include "Modelo/Ativo.h"
#include "Modelo/Dividendo.h"
#include "Modelo/TransacaoImportada.h"
#include <QMap>

typedef QMap<QString, double> DreData;
typedef QMap<QString, double> FluxoCaixaData;

// Forward declarations para as classes de rede
class QNetworkAccessManager;
class QNetworkReply;

struct HistoricoPatrimonio {
    QString mes; // "2025-08"
    double valor;
};

struct PontoTendencia {
    QString mes; // "2025-08"
    double total;
};

// DEFINIÇÃO DA STRUCT PARA O RESULTADO DA SIMULAÇÃO
struct LinhaCronograma {
    int mes;
    QString nomeDivida;
    double valorPago;
    double saldoRestante;
};

struct ResultadoIR {
    double totalVendas;
    double lucroApurado;
    bool isento;
    double impostoDevido;
};

Q_DECLARE_METATYPE(ResultadoIR)


class LancamentoDAO : public QObject
{

    Q_OBJECT
public:
    explicit LancamentoDAO(QObject *parent = nullptr);

    // --- MÉTODOS PÚBLICOS (INICIAM AS REQUISIÇÕES) ---
    // Todos recebem o 'token' para autenticação
    void adicionarLancamento(const Lancamento& lancamento, const QString& token);
    void obterTodos(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta);
    void obterRecentes(const QString& token, int limite = 10);
    void obterResumosDoMes(const QString& token);
    void obterGastosPorCategoria(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta);
    void editarLancamento(const Lancamento& lancamento, const QString& token);
    void excluirLancamento(int idLancamento, const QString& token);
    void obterTodasCategorias(const QString& token);
    void adicionarCategoria(const Categoria& categoria, const QString& token);
    void editarCategoria(const Categoria& categoria, const QString& token);
    void excluirCategoria(int idCategoria, const QString& token);
    void obterTodasContas(const QString& token);
    void adicionarConta(const Conta& conta, const QString& token);
    void editarConta(const Conta& conta, const QString& token);
    void excluirConta(int idConta, const QString& token);
    void obterComparativoMensal(const QString& token, const QDate& dataInicio, const QDate& dataFim, int idConta);
    void obterTodasMetas(const QString& token);
    void adicionarMeta(const Meta& meta, const QString& token);
    void editarMeta(const Meta& meta, const QString& token);
    void excluirMeta(int idMeta, const QString& token);
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
    void obterHistoricoPatrimonio(const QString& token);
    void obterTendenciaCategoria(int idCategoria, const QString& token);
    void simularPlanoQuitacao(double valorExtra, const QString& estrategia, const QString& token);
    void obterDre(const QString& token, const QDate& dataInicio, const QDate& dataFim);
    void obterFluxoCaixa(const QString& token, const QDate& dataInicio, const QDate& dataFim);
    void processarExtratoOcr(const QString& caminhoPdf, const QString& token);
    void obterSugestoesCategorias(const QVector<QString>& descricoes, const QString& token);
    void simularAposentadoria(int idadeAtual, int idadeAposentadoria, double saldoInicial, double aporteMensal, double rentabilidadeAnual, const QString& token);
    void simularFinanciamento(double valorBem, double valorEntrada, double taxaJurosAnual, int numParcelas, const QString& token);
    void simularCambio(const QString& moedaOrigem, const QString& moedaDestino, double valor, const QString& token);
    void calcularIRsobreAcoes(int mes, int ano, const QString& token);

signals:
        // --- SINAIS DE RESULTADO (A RESPOSTA PARA A INTERFACE) ---
    void lancamentoAdicionado();
    void lancamentosRecebidos(const QVector<Lancamento>& lancamentos);
    void resumosRecebidos(double receitas, double despesas);
    void gastosPorCategoriaRecebidos(const QHash<QString, double>& dadosGrafico);
    void erroOcorrido(const QString& mensagem); // Um único sinal de erro genérico
    void lancamentoModificadoComSucesso();
    void lancamentoExcluidoComSucesso();
    void contasRecebidas(const QVector<Conta>& contas);
    void categoriasRecebidas(const QVector<Categoria>& categorias);
    void categoriaModificadaComSucesso(); // Um único sinal para add, edit, delete
    void contaModificadaComSucesso();
    void comparativoMensalRecebido(const QVector<ResumoMensal>& resumo);
    void metasRecebidas(const QVector<Meta>& metas);
    void metaModificadaComSucesso();
    void ativosRecebidos(const QVector<Ativo>& ativos);
    void ativoModificadoComSucesso();
    void operacoesRecebidas(const QVector<OperacaoInvestimento>& operacoes);
    void operacaoModificadaComSucesso();
    void performancePortfolioRecebida(double custoTotal, double valorMercado, double rentabilidadeValor, double rentabilidadePercentual);
    void dividendoAdicionadoComSucesso();
    void dividendosRecebidos(const QVector<Dividendo>& dividendos);
    void historicoPatrimonioRecebido(const QVector<HistoricoPatrimonio>& historico);
    void tendenciaCategoriaRecebida(const QVector<PontoTendencia>& tendencia);
    void planoSimuladoRecebido(const QVector<LinhaCronograma>& cronograma, int mesesTotais);
    void dreRecebido(const DreData& dre);
    void fluxoCaixaRecebido(const FluxoCaixaData& fluxoCaixa);
    void ocrProcessadoComSucesso(const QVector<TransacaoImportada>& transacoes);
    void sugestoesRecebidas(const QMap<QString, int>& mapaDeSugestoes);
    void simulacaoAposentadoriaRecebida(double valorFinal, double totalInvestido, double jurosTotais);
    void simulacaoFinanciamentoRecebida(double valorParcela, double totalPago, double totalJuros);
    void simulacaoCambioRecebida(double valorConvertido);
    void calculoIRRecebido(const ResultadoIR& resultado);

private slots:
    // --- SLOTS PRIVADOS (PROCESSAM AS RESPOSTAS DO SERVIDOR) ---
    void onAdicionarLancamentoReply(QNetworkReply *reply);
    void onObterLancamentosReply(QNetworkReply *reply);
    void onObterResumosReply(QNetworkReply *reply);
    void onObterGastosCategoriaReply(QNetworkReply *reply);
    void onObterContasReply(QNetworkReply *reply);
    void onObterCategoriasReply(QNetworkReply *reply);
    void onModificarCategoriaReply(QNetworkReply *reply);
    void onObterComparativoMensalReply(QNetworkReply *reply);
    void onMetasReply(QNetworkReply *reply);
    void onModificarMetaReply(QNetworkReply *reply);
    void onAtivosReply(QNetworkReply *reply);
    void onModificarAtivoReply(QNetworkReply *reply);
    void onOperacoesReply(QNetworkReply *reply);
    void onModificarOperacaoReply(QNetworkReply *reply);
    void onDividendosReply(QNetworkReply *reply);
    void onPlanoSimuladoReply(QNetworkReply *reply);
    void onSugestoesReply(QNetworkReply *reply);
    void onSimulacaoAposentadoriaReply(QNetworkReply *reply);
    void onSimulacaoFinanciamentoReply(QNetworkReply *reply);
    void onSimulacaoCambioReply(QNetworkReply *reply);
    void onCalculoIRReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
    QString m_baseUrl = "http://localhost:3000/api/lancamentos";

};

#endif // LANCAMENTODAO_H