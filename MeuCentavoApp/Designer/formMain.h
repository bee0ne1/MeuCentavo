#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "Modelo/Usuario.h"

class formUsuario;

QT_BEGIN_NAMESPACE
namespace Ui {
    class formMain;
}
QT_END_NAMESPACE

class formMain : public QMainWindow {
    Q_OBJECT

public:

    explicit formMain(QSqlDatabase db, QWidget *parent = nullptr);

    ~formMain();
    void carregarUltimoUsuario(); // Função pública para atualizar o botão

private slots:
    void abrirTelaUsuario();

private:
    Ui::formMain *ui;
    formUsuario *usuarioWindow = nullptr;
    QSqlDatabase m_db; // Variável membro para GUARDAR a conexão recebida.
    Usuario m_usuarioAtual; // Variável para guardar os dados do usuário logado
    void atualizarBoasVindas(); // Função para atualizar a UI

};

#endif // FORMMAIN_H
