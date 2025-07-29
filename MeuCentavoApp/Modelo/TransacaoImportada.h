// Em Modelo/TransacaoImportada.h

#ifndef TRANSACAOIMPORTADA_H
#define TRANSACAOIMPORTADA_H

#include <QString>

// Struct para guardar os dados brutos de uma linha do CSV
struct TransacaoImportada {
    QString dataStr;
    QString descricaoStr;
    QString valorEntradaStr; // Coluna de créditos/receitas
    QString valorSaidaStr;   // Coluna de débitos/despesas

    // Campos que o usuário irá preencher na tela de mapeamento
    int id_categoria = -1;
    bool ignorar = false;
};

#endif // TRANSACAOIMPORTADA_H