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

// Forward declarations para as classes de rede
class QNetworkAccessManager;
class QNetworkReply;

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
    void editarCategoria(int idCategoria, const QString& novoNome, const QString& token);
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

    signals:



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

private:
    QNetworkAccessManager *m_manager;
    QString m_baseUrl = "http://localhost:3000/api/lancamentos";
};

#endif // LANCAMENTODAO_H