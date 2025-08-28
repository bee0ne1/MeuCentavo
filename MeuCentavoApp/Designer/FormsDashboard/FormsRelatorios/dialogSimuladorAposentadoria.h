#ifndef DIALOGSIMULADORAPOSENTADORIA_H
#define DIALOGSIMULADORAPOSENTADORIA_H

#include <QDialog>
#include "DataAccess/RelatorioDAO.h"

// Forward declarations
namespace Ui {
    class dialogSimuladorAposentadoria;
}

class dialogSimuladorAposentadoria : public QDialog
{
    Q_OBJECT

public:
    explicit dialogSimuladorAposentadoria(QWidget *parent = nullptr);
    ~dialogSimuladorAposentadoria();

private slots:
    // Slot que será chamado pelo clique do botão "Calcular"
    void on_buttonCalcular_clicked();

    // Slot para receber o resultado do cálculo vindo do DAO
    void onSimulacaoRecebida(double valorFinal, double totalInvestido, double jurosTotais);

    // Slot para tratar erros de rede
    void onErro(const QString& motivo);

private:
    Ui::dialogSimuladorAposentadoria *ui;
    RelatorioDAO* m_dao; // O DAO que fará a comunicação com a API
};

#endif // DIALOGSIMULADORAPOSENTADORIA_H
