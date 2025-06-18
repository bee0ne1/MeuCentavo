/********************************************************************************
** Form generated from reading UI file 'formCadastro.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCADASTRO_H
#define UI_FORMCADASTRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formCadastro
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *formCadastro)
    {
        if (formCadastro->objectName().isEmpty())
            formCadastro->setObjectName("formCadastro");
        formCadastro->resize(800, 600);
        formCadastro->setMinimumSize(QSize(800, 600));
        formCadastro->setMaximumSize(QSize(800, 600));
        formCadastro->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 88, 255)"));
        label = new QLabel(formCadastro);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 10, 191, 131));
        QFont font;
        font.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond")});
        font.setPointSize(24);
        label->setFont(font);
        label_2 = new QLabel(formCadastro);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 90, 151, 31));

        retranslateUi(formCadastro);

        QMetaObject::connectSlotsByName(formCadastro);
    } // setupUi

    void retranslateUi(QWidget *formCadastro)
    {
        formCadastro->setWindowTitle(QCoreApplication::translate("formCadastro", "formCadastro", nullptr));
        label->setText(QCoreApplication::translate("formCadastro", "MEU CENTAVO", nullptr));
        label_2->setText(QCoreApplication::translate("formCadastro", "CADASTRO DE USU\303\201RIO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formCadastro: public Ui_formCadastro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCADASTRO_H
