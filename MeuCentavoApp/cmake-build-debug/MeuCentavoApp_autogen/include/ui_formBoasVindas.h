/********************************************************************************
** Form generated from reading UI file 'formBoasVindas.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMBOASVINDAS_H
#define UI_FORMBOASVINDAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formBoasVindas
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *buttonCriarUsuario;

    void setupUi(QWidget *formBoasVindas)
    {
        if (formBoasVindas->objectName().isEmpty())
            formBoasVindas->setObjectName("formBoasVindas");
        formBoasVindas->resize(800, 600);
        formBoasVindas->setMinimumSize(QSize(800, 600));
        formBoasVindas->setMaximumSize(QSize(800, 600));
        formBoasVindas->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 88, 255)"));
        label = new QLabel(formBoasVindas);
        label->setObjectName("label");
        label->setGeometry(QRect(290, 20, 208, 68));
        QFont font;
        font.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond")});
        font.setPointSize(24);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(formBoasVindas);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(260, 200, 261, 91));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond")});
        font1.setPointSize(36);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        buttonCriarUsuario = new QPushButton(formBoasVindas);
        buttonCriarUsuario->setObjectName("buttonCriarUsuario");
        buttonCriarUsuario->setGeometry(QRect(310, 320, 151, 51));

        retranslateUi(formBoasVindas);

        QMetaObject::connectSlotsByName(formBoasVindas);
    } // setupUi

    void retranslateUi(QWidget *formBoasVindas)
    {
        formBoasVindas->setWindowTitle(QCoreApplication::translate("formBoasVindas", "formBoasVindas", nullptr));
        label->setText(QCoreApplication::translate("formBoasVindas", "MEU CENTAVO", nullptr));
        label_2->setText(QCoreApplication::translate("formBoasVindas", "BEM VINDO", nullptr));
        buttonCriarUsuario->setText(QCoreApplication::translate("formBoasVindas", "Criar um usu\303\241rio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formBoasVindas: public Ui_formBoasVindas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMBOASVINDAS_H
