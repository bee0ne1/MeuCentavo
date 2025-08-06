//
// Created by bruno on 18/07/25.
//

#ifndef CONTA_H
#define CONTA_H

#include <QString>
#include <QDate>
struct Conta
{
    int id;
    QString nome;
    QString tipo_conta;
    double saldo_inicial;
    int id_usuario;
    QString moeda_codigo;
    // --- NOVOS CAMPOS PARA DÍVIDAS ---
    double taxa_juros;
    double valor_total_divida;
    QDate data_vencimento;
};






#endif //CONTA_H
