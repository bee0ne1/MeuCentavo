#ifndef DIALOGCALCULADORAIR_H
#define DIALOGCALCULADORAIR_H

#include <QDialog>
#include "DataAccess/LancamentoDAO.h" // Para a struct

class LancamentoDAO;
namespace Ui { class dialogCalculadoraIR; }

class dialogCalculadoraIR : public QDialog
{
    Q_OBJECT

public:
    explicit dialogCalculadoraIR(QWidget *parent = nullptr);
    ~dialogCalculadoraIR();

private slots:
    void on_buttonCalcular_clicked();
    void onCalculoRecebido(const ResultadoIR& resultado);
    void onErro(const QString& motivo);

private:
    void popularCamposData();

    Ui::dialogCalculadoraIR *ui;
    LancamentoDAO* m_dao;
};

#endif // DIALOGCALCULADORAIR_H