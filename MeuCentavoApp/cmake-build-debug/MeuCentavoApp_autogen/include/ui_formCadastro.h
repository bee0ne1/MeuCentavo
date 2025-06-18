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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formCadastro
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;

    void setupUi(QWidget *formCadastro)
    {
        if (formCadastro->objectName().isEmpty())
            formCadastro->setObjectName("formCadastro");
        formCadastro->resize(800, 600);
        formCadastro->setMinimumSize(QSize(800, 600));
        formCadastro->setMaximumSize(QSize(800, 600));
        formCadastro->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 88, 255)"));
        verticalLayout = new QVBoxLayout(formCadastro);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_4 = new QLabel(formCadastro);
        label_4->setObjectName("label_4");
        QFont font;
        font.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond")});
        font.setPointSize(14);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_4, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 1);

        label_3 = new QLabel(formCadastro);
        label_3->setObjectName("label_3");
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        lineEdit_2 = new QLineEdit(formCadastro);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout->addWidget(lineEdit_2, 4, 2, 1, 1);

        label_2 = new QLabel(formCadastro);
        label_2->setObjectName("label_2");
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_2, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 3, 1, 1);

        label_5 = new QLabel(formCadastro);
        label_5->setObjectName("label_5");
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_5, 5, 1, 1, 1);

        lineEdit_3 = new QLineEdit(formCadastro);
        lineEdit_3->setObjectName("lineEdit_3");

        gridLayout->addWidget(lineEdit_3, 5, 2, 1, 1);

        lineEdit = new QLineEdit(formCadastro);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 3, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 2, 1, 1);

        label = new QLabel(formCadastro);
        label->setObjectName("label");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond")});
        font1.setPointSize(24);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(formCadastro);

        QMetaObject::connectSlotsByName(formCadastro);
    } // setupUi

    void retranslateUi(QWidget *formCadastro)
    {
        formCadastro->setWindowTitle(QCoreApplication::translate("formCadastro", "formCadastro", nullptr));
        label_4->setText(QCoreApplication::translate("formCadastro", "USU\303\201RIO", nullptr));
        label_3->setText(QCoreApplication::translate("formCadastro", "C\303\223DIGO", nullptr));
        label_2->setText(QCoreApplication::translate("formCadastro", "CADASTRO", nullptr));
        label_5->setText(QCoreApplication::translate("formCadastro", "SENHA", nullptr));
        label->setText(QCoreApplication::translate("formCadastro", "MEU CENTAVO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formCadastro: public Ui_formCadastro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCADASTRO_H
