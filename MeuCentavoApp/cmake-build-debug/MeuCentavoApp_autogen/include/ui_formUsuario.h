/********************************************************************************
** Form generated from reading UI file 'formUsuario.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMUSUARIO_H
#define UI_FORMUSUARIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formUsuario
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *layoutUsuarios;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *buttonBack;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *buttonCadastro;
    QLineEdit *lineEdit_2;
    QPushButton *buttonExcluirUsuarios;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *formUsuario)
    {
        if (formUsuario->objectName().isEmpty())
            formUsuario->setObjectName("formUsuario");
        formUsuario->resize(800, 600);
        formUsuario->setMinimumSize(QSize(800, 600));
        formUsuario->setMaximumSize(QSize(800, 600));
        formUsuario->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 88, 255)"));
        gridLayout = new QGridLayout(formUsuario);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(formUsuario);
        label->setObjectName("label");
        label->setMaximumSize(QSize(800, 100));
        QFont font;
        font.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond Light")});
        font.setPointSize(24);
        font.setWeight(QFont::Light);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font: 300 24pt \"Noto Sans Arabic Cond Light\";"));
        label->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 1);

        layoutUsuarios = new QHBoxLayout();
        layoutUsuarios->setObjectName("layoutUsuarios");
        layoutUsuarios->setContentsMargins(-1, 0, -1, -1);

        gridLayout->addLayout(layoutUsuarios, 2, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        buttonBack = new QPushButton(formUsuario);
        buttonBack->setObjectName("buttonBack");
        buttonBack->setMinimumSize(QSize(200, 0));
        buttonBack->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(buttonBack);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_3, 5, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 68, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 6, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        buttonCadastro = new QPushButton(formUsuario);
        buttonCadastro->setObjectName("buttonCadastro");
        buttonCadastro->setMinimumSize(QSize(200, 0));
        buttonCadastro->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_2->addWidget(buttonCadastro);

        lineEdit_2 = new QLineEdit(formUsuario);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setMinimumSize(QSize(200, 0));
        lineEdit_2->setMaximumSize(QSize(200, 16777215));
        lineEdit_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(lineEdit_2);

        buttonExcluirUsuarios = new QPushButton(formUsuario);
        buttonExcluirUsuarios->setObjectName("buttonExcluirUsuarios");

        horizontalLayout_2->addWidget(buttonExcluirUsuarios);


        gridLayout->addLayout(horizontalLayout_2, 3, 1, 2, 2);

        verticalSpacer = new QSpacerItem(20, 68, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);


        retranslateUi(formUsuario);

        QMetaObject::connectSlotsByName(formUsuario);
    } // setupUi

    void retranslateUi(QWidget *formUsuario)
    {
        formUsuario->setWindowTitle(QCoreApplication::translate("formUsuario", "formUsuario", nullptr));
        label->setText(QCoreApplication::translate("formUsuario", "MEU CENTAVO", nullptr));
        buttonBack->setText(QCoreApplication::translate("formUsuario", "Voltar a tela de in\303\255cio", nullptr));
        buttonCadastro->setText(QCoreApplication::translate("formUsuario", "Cadastrar novo usu\303\241rio", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("formUsuario", "Adicionar novo usu\303\241rio", nullptr));
        buttonExcluirUsuarios->setText(QCoreApplication::translate("formUsuario", "Excluir usu\303\241rios", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formUsuario: public Ui_formUsuario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMUSUARIO_H
