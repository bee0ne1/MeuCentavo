#ifndef PAGELANCAMENTOS_H
#define PAGELANCAMENTOS_H

#include <QWidget>
#include <QVector>
#include "Modelo/Lancamento.h"
#include "Modelo/Conta.h"
#include "Modelo/TransacaoImportada.h"
#include <QMap>

// Forward declarations
namespace Ui { class pageLancamentos; }
class LancamentoDAO;
class ContaDAO;
class formAdicionarLancamento;

class pageLancamentos : public QWidget
{
    Q_OBJECT

public:
    // Construtor muito mais simples. Ele buscará as informações de sessão por conta própria.
    explicit pageLancamentos(QWidget *parent = nullptr);
    ~pageLancamentos();
signals:
    void dadosAtualizados();

public slots:
    // Slot para (re)carregar os dados da tabela, agora ele apenas inicia a requisição.
    void carregarTabela();
    void onOcrConcluido(const QVector<TransacaoImportada>& transacoes);

private slots:
    // Slot para o botão "Adicionar Lançamento"
    void abrirDialogoAdicionar();


    // Slots para receber as respostas da API através do DAO
    void onLancamentosRecebidos(const QVector<Lancamento>& lancamentos);
    void onErroDeRede(const QString& motivo);
    void editarLancamento(const Lancamento& lancamento);
    void excluirLancamento(const Lancamento& lancamento);
    void onContasRecebidas(const QVector<Conta>& contas);
    void on_buttonImportarExtrato_clicked();
    void onSugestoesParaMapeamentoRecebidas(const QMap<QString, int>& sugestoes);

private:
    Ui::pageLancamentos *ui;
    LancamentoDAO* m_dao;
    ContaDAO* m_contaDAO;
    formAdicionarLancamento* m_dialogoAdicionar;
    QVector<TransacaoImportada> m_transacoesLidas;
    int m_idContaImportacao;
};

#endif // PAGELANCAMENTOS_H