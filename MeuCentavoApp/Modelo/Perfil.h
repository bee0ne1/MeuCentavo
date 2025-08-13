#ifndef PERFIL_H
#define PERFIL_H
#include <QString>
#include <QMetaType>

struct Perfil {
    int id_perfil;
    int id_usuario;
    QString nome_perfil;
    QString tipo_perfil; // "PF" ou "PJ"
    QString documento;   // CPF ou CNPJ
    QString razao_social;
};

Q_DECLARE_METATYPE(Perfil);

#endif // PERFIL_H