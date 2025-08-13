#ifndef DIALOGADDEDITCATEGORIA_H
#define DIALOGADDEDITCATEGORIA_H

#include <QDialog>
#include "Modelo/Categoria.h"

namespace Ui { class dialogAddEditCategoria; }

class dialogAddEditCategoria : public QDialog
{
    Q_OBJECT
public:
    // O construtor recebe o tipo de perfil para se adaptar
    explicit dialogAddEditCategoria(const QString& tipoPerfil, QWidget *parent = nullptr);
    ~dialogAddEditCategoria();

    // Funções para preencher dados (edição) e obter dados (salvar)
    void setDados(const Categoria& categoria);
    Categoria getDados() const;

private:
    Ui::dialogAddEditCategoria *ui;
    int m_idCategoria;
    QString m_tipoPerfil;
};
#endif // DIALOGADDEDITCATEGORIA_H
