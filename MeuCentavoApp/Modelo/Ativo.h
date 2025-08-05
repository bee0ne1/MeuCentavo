#ifndef ATIVO_H
#define ATIVO_H

#include <QString>

// Representa um registo da tabela 'ativos'
struct Ativo {
    int id_ativo;
    int id_usuario;
    QString ticker;
    QString nome;
    QString tipo_ativo;
    double quantidade_total;
    double custo_total;
    QString moeda_codigo;
};

#endif // ATIVO_H