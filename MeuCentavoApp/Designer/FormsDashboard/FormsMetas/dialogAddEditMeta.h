#ifndef DIALOGADDEDITMETA_H
#define DIALOGADDEDITMETA_H

#include <QDialog>
#include "Modelo/Meta.h"

namespace Ui {
    class dialogAddEditMeta;
}

class dialogAddEditMeta : public QDialog
{
    Q_OBJECT

public:
    explicit dialogAddEditMeta(QWidget *parent = nullptr);
    ~dialogAddEditMeta();

    // Usada para preencher o formulário no modo de edição
    void setMeta(const Meta& meta);

    // Usada para obter os dados preenchidos pelo usuário
    Meta getMeta() const;

public slots:
    void accept() override;

private:
    Ui::dialogAddEditMeta *ui;
    int m_idMeta; // Guarda o ID da meta quando em modo de edição
};

#endif // DIALOGADDEDITMETA_H