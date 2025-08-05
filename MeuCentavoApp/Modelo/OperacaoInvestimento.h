#ifndef OPERACAOINVESTIMENTO_H
#define OPERACAOINVESTIMENTO_H

#include <QDate>
#include <QString>

// Representa um registo da tabela 'operacoes_investimentos'
struct OperacaoInvestimento {
    int id_operacao;
    int id_ativo;
    QString tipo_operacao; // "Compra" ou "Venda"
    QDate data_operacao;
    double quantidade;
    double preco_unitario;
    double custos;
    QString moeda_codigo;
    double taxa_cambio_usada;
};

#endif // OPERACAOINVESTIMENTO_H
