#ifndef FORMINICIO_H
#define FORMINICIO_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "Modelo/Usuario.h"

class formUsuario;

QT_BEGIN_NAMESPACE
namespace Ui {
    class formInicio;
}
QT_END_NAMESPACE

class formInicio : public QMainWindow {
    Q_OBJECT

public:

    explicit formInicio(QSqlDatabase db, QWidget *parent = nullptr);

    ~formInicio();


public slots:
    void carregarUsuarioInicial();
    void atualizarUsuarioNoBotao(const Usuario& usuario);

private slots:
    void abrirTelaUsuario();


private:
    Ui::formInicio *ui;
    formUsuario *usuarioWindow = nullptr;
    QSqlDatabase m_db; // Variável membro para GUARDAR a conexão recebida.
    Usuario m_usuarioAtual; // Variável para guardar os dados do usuário logado
    void atualizarBoasVindas(); // Função para atualizar a UI

};

#endif // FORMINICIO_H
