#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QMainWindow>
#include "Forms/formCadastro.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class formMain;
}
QT_END_NAMESPACE

class formMain : public QMainWindow {
    Q_OBJECT

public:
    explicit formMain(QWidget *parent = nullptr);
    ~formMain();

private slots:
    void abrirTelaCadastro();

private:
    Ui::formMain *ui;
    formCadastro *cadastroWindow;
};

#endif // FORMMAIN_H
