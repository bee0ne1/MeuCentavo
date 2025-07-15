#ifndef FORMCADASTRO_H
#define FORMCADASTRO_H

#include <QDialog>
#include "Composicoes/PasswordFormHelper.h" // Assumindo que o helper está aqui

// Forward declaration
namespace Ui { class formCadastro; }

class formCadastro : public QDialog
{
    Q_OBJECT

public:
    explicit formCadastro(QWidget *parent = nullptr);
    ~formCadastro();

signals:
    // Sinal para avisar que o processo foi concluído com sucesso
    void cadastroConcluido();

private slots:
    // Slots para a lógica da UI
    void gravarUsuario();
    void verificarCampos();

    // Slots para reagir às respostas do DAO
    void onRegistroSucesso();
    void onRegistroFalhou(const QString& motivo);

private:
    Ui::formCadastro *ui;
    PasswordFormHelper *m_passwordHelper;
};

#endif // FORMCADASTRO_H