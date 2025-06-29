#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QMainWindow>
#include <QSqlDatabase>

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

private slots:
    void abrirTelaUsuario();

private:
    Ui::formMain *ui;
    formUsuario *usuarioWindow = nullptr;
    QSqlDatabase m_db; // Variável membro para GUARDAR a conexão recebida.
};

#endif // FORMMAIN_H
