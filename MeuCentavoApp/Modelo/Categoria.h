//
// Created by bruno on 18/07/25.
//

#ifndef CATEGORIA_H
#define CATEGORIA_H

#include <QString>

struct Categoria
{
    int id;
    QString nome;
    QString tipo;
    int id_usuario;
    int id_perfil;
    QString classificacao_contabil;
};


#endif //CATEGORIA_H
