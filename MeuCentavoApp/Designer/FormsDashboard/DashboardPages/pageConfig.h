//
// Created by bruno on 21/07/25.
//

#ifndef PAGECONFIG_H
#define PAGECONFIG_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class pageConfig; }
QT_END_NAMESPACE

class pageConfig : public QWidget {
Q_OBJECT

public:
    explicit pageConfig(QWidget *parent = nullptr);
    ~pageConfig() override;

private slots:
    void on_buttonCategorias_clicked();

private:
    Ui::pageConfig *ui;

};


#endif //PAGECONFIG_H
