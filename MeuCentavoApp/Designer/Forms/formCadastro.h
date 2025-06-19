#ifndef FORMCADASTRO_H
#define FORMCADASTRO_H

#include <QWidget>
class formUsuario;

QT_BEGIN_NAMESPACE
namespace Ui {
    class formCadastro;
}
QT_END_NAMESPACE

class formCadastro : public QWidget {
    Q_OBJECT

public:
    explicit formCadastro(formUsuario *usuario,QWidget *parent = nullptr);
    ~formCadastro();

signals:
    void cadastroFechado();

private slots:
    void verificarCampos();
    void visualizarSenha();
    void cancelarCadastro();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::formCadastro *ui;
    formUsuario *usuarioWindow = nullptr;
};

#endif // FORMCADASTRO_H
