#ifndef DIALOGSIMULADORCAMBIO_H
#define DIALOGSIMULADORCAMBIO_H

#include <QDialog>

class LancamentoDAO;
namespace Ui { class dialogSimuladorCambio; }

class dialogSimuladorCambio : public QDialog
{
    Q_OBJECT

public:
    explicit dialogSimuladorCambio(QWidget *parent = nullptr);
    ~dialogSimuladorCambio();

private slots:
    void on_buttonConverter_clicked();
    void onSimulacaoRecebida(double valorConvertido);
    void onErro(const QString& motivo);

private:
    void popularComboBoxes();

    Ui::dialogSimuladorCambio *ui;
    LancamentoDAO* m_dao;
};

#endif // DIALOGSIMULADORCAMBIO_H
