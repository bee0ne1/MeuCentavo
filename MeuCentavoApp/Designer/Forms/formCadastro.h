#ifndef FORMCADASTRO_H
#define FORMCADASTRO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class formCadastro;
}
QT_END_NAMESPACE

class formCadastro : public QWidget {
    Q_OBJECT

public:
    explicit formCadastro(QWidget *parent = nullptr);
    ~formCadastro();

    signals:
        void cadastroFechado();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::formCadastro *ui;
};

#endif // FORMCADASTRO_H
