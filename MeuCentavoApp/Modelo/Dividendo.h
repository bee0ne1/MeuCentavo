// Em Modelo/Dividendo.h
#ifndef DIVIDENDO_H
#define DIVIDENDO_H

#include <QDate>

struct Dividendo {
    int id_dividendo;
    int id_ativo;
    int id_usuario;
    QDate data_pagamento;
    double valor_total;
};

#endif // DIVIDENDO_H