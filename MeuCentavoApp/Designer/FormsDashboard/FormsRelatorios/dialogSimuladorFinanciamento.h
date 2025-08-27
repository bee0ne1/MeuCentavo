#ifndef DIALOGSIMULADORFINANCIAMENTO_H
#define DIALOGSIMULADORFINANCIAMENTO_H

#include <QDialog>

// Forward declarations para evitar includes desnecessários no .h
namespace Ui {
    class dialogSimuladorFinanciamento;
}
class LancamentoDAO;

class dialogSimuladorFinanciamento : public QDialog
{
    Q_OBJECT

public:
    explicit dialogSimuladorFinanciamento(QWidget *parent = nullptr);
    ~dialogSimuladorFinanciamento();

private slots:
    // Slot conectado ao clique do botão "Calcular"
    void on_buttonCalcular_clicked();

    // Slot que recebe o resultado do backend via DAO
    void onSimulacaoRecebida(double valorParcela, double totalPago, double totalJuros);

    // Slot para tratar erros de rede
    void onErro(const QString& motivo);

private:
    Ui::dialogSimuladorFinanciamento *ui;
    LancamentoDAO* m_dao;
};

#endif // DIALOGSIMULADORFINANCIAMENTO_H