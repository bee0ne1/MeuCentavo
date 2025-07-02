#ifndef FORMCADASTRO_H
#define FORMCADASTRO_H

#include <QWidget>
#include <QSqlDatabase>

class formUsuario;

QT_BEGIN_NAMESPACE
namespace Ui {
    class formCadastro;
}
QT_END_NAMESPACE

class formCadastro : public QWidget {
    Q_OBJECT

public:
    explicit formCadastro(QSqlDatabase db, QWidget *parent = nullptr);
    ~formCadastro();

signals:
    void cadastroFechado();
     void cadastroConcluido();

private slots:
    void verificarCampos();
    void visualizarSenha();
    void cancelarCadastro();
    void gravarUsuario();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::formCadastro *ui;
    formUsuario *usuarioWindow = nullptr;
     QSqlDatabase m_db;
};

#endif // FORMCADASTRO_H
