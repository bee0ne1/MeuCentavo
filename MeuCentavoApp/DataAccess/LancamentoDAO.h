#ifndef LANCAMENTODAO_H
#define LANCAMENTODAO_H

#include <QObject>
#include <QVector>
#include <QHash>
#include "Modelo/Lancamento.h"
#include "Modelo/Conta.h" // Crie estes ficheiros de modelo se necessário
#include "Modelo/Categoria.h"

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
    void obterTodos(const QString& token);
    void obterRecentes(const QString& token, int limite = 10);
    void obterResumosDoMes(const QString& token);
    void obterGastosPorCategoria(const QString& token);
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

private slots:
    // --- SLOTS PRIVADOS (PROCESSAM AS RESPOSTAS DO SERVIDOR) ---
    void onAdicionarLancamentoReply(QNetworkReply *reply);
    void onObterLancamentosReply(QNetworkReply *reply);
    void onObterResumosReply(QNetworkReply *reply);
    void onObterGastosCategoriaReply(QNetworkReply *reply);
    void onObterContasReply(QNetworkReply *reply);
    void onObterCategoriasReply(QNetworkReply *reply);
    void onModificarCategoriaReply(QNetworkReply *reply);


private:
    QNetworkAccessManager *m_manager;
    QString m_baseUrl = "http://localhost:3000/api/lancamentos";
};

#endif // LANCAMENTODAO_H