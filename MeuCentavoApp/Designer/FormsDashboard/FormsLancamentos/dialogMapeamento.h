// Em dialogoMapeamento.h

#ifndef DIALOGOMAPEAMENTO_H
#define DIALOGOMAPEAMENTO_H

#include <QDialog>
#include <QVector>
#include "Modelo/TransacaoImportada.h"
#include "Modelo/Categoria.h"

namespace Ui {
    class dialogMapeamento;
}

class LancamentoDAO;

class dialogMapeamento : public QDialog
{
    Q_OBJECT

public:
    // O construtor recebe a lista de transações lidas do arquivo
    explicit dialogMapeamento(QVector<TransacaoImportada>& transacoes, QWidget *parent = nullptr);
    ~dialogMapeamento();

    // Função para obter as transações finalizadas pelo usuário
    QVector<TransacaoImportada> getTransacoesFinalizadas();

private slots:
    void onCategoriasRecebidas(const QVector<Categoria>& categorias);


private:
    void popularTabela();

    Ui::dialogMapeamento *ui;
    LancamentoDAO* m_dao;
    QVector<TransacaoImportada>& m_transacoes; // Uma referência para a lista original
    QVector<Categoria> m_categorias; // Armazena as categorias do usuário
};

#endif // DIALOGOMAPEAMENTO_H