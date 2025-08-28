#ifndef PAGEDIVIDAS_H
#define PAGEDIVIDAS_H

#include <QWidget>
#include "Modelo/Conta.h"
#include "DataAccess/ContaDAO.h"

namespace Ui {
    class pageDividas;
}

class pageDividas : public QWidget
{
    Q_OBJECT

public:
    explicit pageDividas(QWidget *parent = nullptr);
    ~pageDividas();

    // Função pública para ser chamada quando a página ficar visível
    void carregarDados();

private slots:
    // Slot para receber os dados do DAO
    void onDadosRecebidos(const QVector<Conta>& contas);
    void on_buttonPlanejarQuitacao_clicked();


private:
    Ui::pageDividas *ui;
    ContaDAO* m_dao;
};

#endif // PAGEDIVIDAS_H