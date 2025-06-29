//
// Created by bruno on 29/06/25.
//

#ifndef LANCAMENTO_H
#define LANCAMENTO_H

#include <QString>
#include <QDate>

// Esta struct representa um único registro da sua tabela de lançamentos.
// Adapte os campos conforme a sua tabela no banco de dados.
struct Lancamento {
    int id;
    QString descricao;
    double valor;
    QDate data;
    QString tipo; // Ex: "Receita" ou "Despesa"
};

#endif //MEUCENTAVOAPP_LANCAMENTO_H