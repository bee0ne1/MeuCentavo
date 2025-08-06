#ifndef PAGEHOME_H
#define PAGEHOME_H

#include <QWidget>
#include "Modelo/Lancamento.h" // Inclui a struct
#include <QVector>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include "DataAccess/LancamentoDAO.h"


// Forward declarations
namespace Ui { class pageHome; }
class LancamentoDAO;

class pageHome : public QWidget
{
    Q_OBJECT

public:
    // Construtor muito mais simples! Não precisa mais de usuário ou banco.
    explicit pageHome(QWidget *parent = nullptr);
    ~pageHome();
    void atualizarDados(); // Função que inicia as requisições

private slots:
    // Slots para receber os dados vindos da API através do DAO
    void onResumosRecebidos(double receitas, double despesas);
    void onLancamentosRecentesRecebidos(const QVector<Lancamento>& lancamentos);
    void onErroDeRede(const QString& erro);
    void onHistoricoPatrimonioRecebido(const QVector<HistoricoPatrimonio>& historico);



private:

    Ui::pageHome *ui;
    LancamentoDAO* m_dao;
    QChartView *m_chartView;
    QChart *m_chart;
    // Ponteiros para o NOVO gráfico de patrimônio
    QChartView *m_chartViewPatrimonio;
    QChart *m_chartPatrimonio;
};

#endif // PAGEHOME_H