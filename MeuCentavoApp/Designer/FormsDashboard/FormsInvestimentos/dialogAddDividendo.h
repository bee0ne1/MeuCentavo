#ifndef DIALOGADDDIVIDENDO_H
#define DIALOGADDDIVIDENDO_H

#include <QDialog>
#include "Modelo/Ativo.h"       // Precisa saber o que é um Ativo
#include "Modelo/Dividendo.h"   // Precisa saber o que é um Dividendo

// Forward declaration para a classe de UI
namespace Ui {
    class dialogAddDividendo;
}

class dialogAddDividendo : public QDialog
{
    Q_OBJECT

public:
    // O construtor recebe o ativo ao qual o dividendo pertence
    explicit dialogAddDividendo(const Ativo& ativo, QWidget *parent = nullptr);
    ~dialogAddDividendo();

    // Função para a pageInvestimentos obter os dados preenchidos
    Dividendo getDividendo() const;

private:
    Ui::dialogAddDividendo *ui;
    int m_idAtivo; // Guarda o ID do ativo para o qual estamos registrando o dividendo
};

#endif // DIALOGADDDIVIDENDO_H
