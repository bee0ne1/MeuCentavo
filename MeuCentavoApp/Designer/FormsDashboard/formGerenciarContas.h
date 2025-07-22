#ifndef FORMGERENCIARCONTAS_H
#define FORMGERENCIARCONTAS_H

#include <QDialog>
#include "Modelo/Conta.h"

// Forward declarations
class LancamentoDAO;
class QTableWidget;
namespace Ui {
    class formGerenciarContas;
}

class formGerenciarContas : public QDialog
{
    Q_OBJECT

public:
    explicit formGerenciarContas(QWidget *parent = nullptr);
    ~formGerenciarContas();

private slots:
    void onContasRecebidas(const QVector<Conta>& contas);
    void onContaModificada();
    void on_buttonAddConta_clicked();
    void on_buttonEditConta_clicked();
    void on_buttonExcluirConta_clicked();
    void onSelectionChanged();

private:
    void carregarContas();
    void configurarTabela();
    void editarConta(const Conta& conta);
    void excluirConta(const Conta& conta);

    Ui::formGerenciarContas *ui;
    LancamentoDAO* m_dao;
};

#endif // FORMGERENCIARCONTAS_H