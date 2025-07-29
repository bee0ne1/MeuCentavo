#ifndef DIALOGOIMPORTAREXTRATO_H
#define DIALOGOIMPORTAREXTRATO_H

#include <QDialog>
#include <QVector>
#include "Modelo/Conta.h"

namespace Ui {
    class dialogImportarExtrato;
}

class LancamentoDAO;

class dialogImportarExtrato : public QDialog
{
    Q_OBJECT

public:
    explicit dialogImportarExtrato(QWidget *parent = nullptr);
    ~dialogImportarExtrato();

    // Funções para a janela principal obter as seleções do usuário
    QString caminhoArquivoSelecionado() const;
    int idContaSelecionada() const;

private slots:
    void on_buttonSelecionarArquivo_clicked();
    void onContasRecebidas(const QVector<Conta>& contas);

private:
    Ui::dialogImportarExtrato *ui;
    LancamentoDAO* m_dao;
    QString m_caminhoArquivo;
};

#endif // DIALOGOIMPORTAREXTRATO_H