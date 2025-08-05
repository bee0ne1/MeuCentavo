
#ifndef META_H
#define META_H

#include <QString>
#include <QDate>

struct Meta {
    int id_meta;
    int id_usuario;
    QString nome;
    double valor_alvo;
    double valor_atual;
    QDate data_alvo;
    QString moeda_codigo;
};

#endif // META_H