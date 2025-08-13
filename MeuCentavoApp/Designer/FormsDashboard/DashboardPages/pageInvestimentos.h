#ifndef PAGEINVESTIMENTOS_H
#define PAGEINVESTIMENTOS_H

#include <QWidget>
#include "Modelo/Ativo.h"
#include "Modelo/OperacaoInvestimento.h"
#include "Modelo/Dividendo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class pageInvestimentos; }
QT_END_NAMESPACE

class LancamentoDAO;

class pageInvestimentos : public QWidget
{
    Q_OBJECT

public:
    explicit pageInvestimentos(QWidget *parent = nullptr);
    ~pageInvestimentos();

public slots:
    void carregarAtivos();

private slots:
    void onAtivosRecebidos(const QVector<Ativo>& ativos);
    void onAtivoModificado();
    void onErroDeRede(const QString& motivo);

    void on_buttonAdicionarAtivo_clicked();
    void on_buttonEditarAtivo_clicked();
    void on_buttonExcluirAtivo_clicked();
    void on_buttonRegistrarDividendo_clicked();
    void on_buttonRegistrarOperacao_clicked();

    void onAtivoSelecionado(); // Será chamado quando o usuário clicar em uma linha da tabela de ativos
    void onOperacoesRecebidas(const QVector<OperacaoInvestimento>& operacoes);
    void onPerformanceRecebida(double custoTotal, double valorMercado, double rentabilidadeValor, double rentabilidadePercentual);
    void onDividendosRecebidos(const QVector<Dividendo>& dividendos);


    // Adicionaremos os outros botões depois

private:

    Ui::pageInvestimentos *ui;
    LancamentoDAO* m_dao;
    QVector<Ativo> m_ativos;
};

#endif // PAGEINVESTIMENTOS_H