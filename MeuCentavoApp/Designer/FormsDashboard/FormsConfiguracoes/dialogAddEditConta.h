#ifndef DIALOGADDEDITCONTA_H
#define DIALOGADDEDITCONTA_H

#include <QDialog>
#include "Modelo/Conta.h" // Inclui a nossa struct de Conta

namespace Ui {
    class DialogAddEditConta;
}

class DialogAddEditConta : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddEditConta(QWidget *parent = nullptr);
    ~DialogAddEditConta();

    // Função para pré-preencher o formulário no modo de edição
    void setConta(const Conta& conta);

    // Função para obter os dados preenchidos pelo usuário
    Conta getConta() const;

private:
    Ui::DialogAddEditConta *ui;
    int m_idConta; // Para guardar o ID quando estivermos a editar
};

#endif // DIALOGADDEDITCONTA_H