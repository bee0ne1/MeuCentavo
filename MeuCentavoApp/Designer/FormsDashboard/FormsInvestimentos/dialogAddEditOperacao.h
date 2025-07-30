#ifndef DIALOGADDEDITOPERACAO_H
#define DIALOGADDEDITOPERACAO_H

#include <QDialog>
#include "Modelo/OperacaoInvestimento.h"
#include "Modelo/Ativo.h"

namespace Ui {
    class dialogAddEditOperacao;
}

class dialogAddEditOperacao : public QDialog
{
    Q_OBJECT

public:
    // O construtor agora recebe o ativo ao qual a operação pertence
    explicit dialogAddEditOperacao(const Ativo& ativo, QWidget *parent = nullptr);
    ~dialogAddEditOperacao();

    OperacaoInvestimento getOperacao() const;

private:
    Ui::dialogAddEditOperacao *ui;
    int m_idAtivo; // Guarda o ID do ativo
};

#endif // DIALOGADDEDITOPERACAO_H