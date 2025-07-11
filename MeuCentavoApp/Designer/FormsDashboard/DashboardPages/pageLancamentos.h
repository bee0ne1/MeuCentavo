//
// Created by bruno on 11/07/25.
//

#ifndef PAGELANCAMENTOS_H
#define PAGELANCAMENTOS_H

#include <QWidget>
#include "Modelo/Usuario.h"
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class pageLancamentos; }
QT_END_NAMESPACE

class pageLancamentos : public QWidget {
Q_OBJECT

public:
    explicit pageLancamentos(const Usuario& usuario, QSqlDatabase db,QWidget *parent = nullptr);
    ~pageLancamentos() override;

private slots:
    void on_buttonAdicionarLancamento_clicked();
    void carregarTabela(); // Slot para (re)carregar os dados da tabela

private:
    Ui::pageLancamentos *ui;
    QSqlDatabase m_db;
    Usuario m_usuarioAtual;

};


#endif //PAGELANCAMENTOS_H
