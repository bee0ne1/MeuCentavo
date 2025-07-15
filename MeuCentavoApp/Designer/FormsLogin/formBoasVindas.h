#ifndef FORMBOASVINDAS_H
#define FORMBOASVINDAS_H

#include <QWidget>

// Forward declaration para a classe que ele vai abrir
class formCadastro;

namespace Ui {
    class formBoasVindas;
}

class formBoasVindas : public QWidget
{
    Q_OBJECT

public:
    explicit formBoasVindas(QWidget *parent = nullptr);
    ~formBoasVindas();

private slots:
    void abrirTelaCadastro();
    void onCadastroConcluido();

private:
    Ui::formBoasVindas *ui;
    // Não temos mais 'm_db'.
    formCadastro* m_formCadastro;
};

#endif // FORMBOASVINDAS_H