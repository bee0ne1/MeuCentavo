#ifndef PAGERELATORIOS_H
#define PAGERELATORIOS_H

#include <QWidget>
#include <QHash>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include "Modelo/Conta.h"
#include "Modelo/Lancamento.h"
// Forward declarations para Qt Charts e nossas classes
QT_BEGIN_NAMESPACE
namespace Ui { class pageRelatorios; }
QT_END_NAMESPACE


class LancamentoDAO;

class pageRelatorios : public QWidget
{
    Q_OBJECT

public:
    explicit pageRelatorios(QWidget *parent = nullptr);
    ~pageRelatorios();

private slots:
    // Slot para receber os dados do DAO
    void onGastosRecebidos(const QHash<QString, double>& dados);

    void onContasRecebidas(const QVector<Conta>& contas);

    // Slot para tratar erros de rede
    void onErroDeRede(const QString& motivo);
    void onDetalhesRecebidos(const QVector<Lancamento>& lancamentos);
    void onComparativoRecebido(const QVector<ResumoMensal>& resumo);
    void popularTabelaDetalhes(const QVector<Lancamento>& lancamentos);
    void filtrarTabelaPorCategoria(const QString& nomeCategoria);
    // Novo slot para reagir à seleção do ComboBox de período
    void onPeriodoSelecionado(int index);

private:
    // Função auxiliar para iniciar o carregamento dos dados
    void carregarDados();

    Ui::pageRelatorios *ui;
    LancamentoDAO* m_dao;
    QVector<Lancamento> m_lancamentosDoPeriodo;

    // Ponteiros para os gráfico de pizza
    QChartView *m_chartView;
    QChart *m_chart;

    // Ponteiros para o NOVO gráfico de barras
    QChartView *m_chartViewBarras;
    QChart *m_chartBarras;
};

#endif // PAGERELATORIOS_H