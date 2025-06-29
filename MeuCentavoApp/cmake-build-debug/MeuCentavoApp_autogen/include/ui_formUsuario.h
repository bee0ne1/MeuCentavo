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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formUsuario
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *buttonCadastro;
    QPushButton *buttonUsuarioSwitch1;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton;
    QPushButton *buttonUsuarioSwitch2;
    QPushButton *buttonBack;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QPushButton *buttonUsuarioSwitch3;
    QLineEdit *lineEdit_2;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *formUsuario)
    {
        if (formUsuario->objectName().isEmpty())
            formUsuario->setObjectName("formUsuario");
        formUsuario->resize(800, 600);
        formUsuario->setMinimumSize(QSize(800, 600));
        formUsuario->setMaximumSize(QSize(800, 600));
        formUsuario->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 88, 255)"));
        verticalLayout = new QVBoxLayout(formUsuario);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        buttonCadastro = new QPushButton(formUsuario);
        buttonCadastro->setObjectName("buttonCadastro");
        buttonCadastro->setMinimumSize(QSize(200, 0));
        buttonCadastro->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(buttonCadastro, 3, 1, 1, 1);

        buttonUsuarioSwitch1 = new QPushButton(formUsuario);
        buttonUsuarioSwitch1->setObjectName("buttonUsuarioSwitch1");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonUsuarioSwitch1->sizePolicy().hasHeightForWidth());
        buttonUsuarioSwitch1->setSizePolicy(sizePolicy);
        buttonUsuarioSwitch1->setMinimumSize(QSize(200, 200));

        gridLayout->addWidget(buttonUsuarioSwitch1, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 6, 1, 1, 1);

        pushButton = new QPushButton(formUsuario);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 3, 2, 1, 1);

        buttonUsuarioSwitch2 = new QPushButton(formUsuario);
        buttonUsuarioSwitch2->setObjectName("buttonUsuarioSwitch2");
        sizePolicy.setHeightForWidth(buttonUsuarioSwitch2->sizePolicy().hasHeightForWidth());
        buttonUsuarioSwitch2->setSizePolicy(sizePolicy);
        buttonUsuarioSwitch2->setMinimumSize(QSize(200, 200));

        gridLayout->addWidget(buttonUsuarioSwitch2, 2, 1, 1, 1);

        buttonBack = new QPushButton(formUsuario);
        buttonBack->setObjectName("buttonBack");
        buttonBack->setMinimumSize(QSize(200, 0));
        buttonBack->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(buttonBack, 5, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

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

        gridLayout->addWidget(label, 0, 0, 1, 3);

        buttonUsuarioSwitch3 = new QPushButton(formUsuario);
        buttonUsuarioSwitch3->setObjectName("buttonUsuarioSwitch3");
        sizePolicy.setHeightForWidth(buttonUsuarioSwitch3->sizePolicy().hasHeightForWidth());
        buttonUsuarioSwitch3->setSizePolicy(sizePolicy);
        buttonUsuarioSwitch3->setMinimumSize(QSize(200, 200));

        gridLayout->addWidget(buttonUsuarioSwitch3, 2, 2, 1, 1);

        lineEdit_2 = new QLineEdit(formUsuario);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setMinimumSize(QSize(200, 0));
        lineEdit_2->setMaximumSize(QSize(200, 16777215));
        lineEdit_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(lineEdit_2, 3, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 4, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(formUsuario);

        QMetaObject::connectSlotsByName(formUsuario);
    } // setupUi

    void retranslateUi(QWidget *formUsuario)
    {
        formUsuario->setWindowTitle(QCoreApplication::translate("formUsuario", "formUsuario", nullptr));
        buttonCadastro->setText(QCoreApplication::translate("formUsuario", "Cadastrar novo usu\303\241rio", nullptr));
        buttonUsuarioSwitch1->setText(QCoreApplication::translate("formUsuario", "USU\303\201RIO 1", nullptr));
        pushButton->setText(QCoreApplication::translate("formUsuario", "Editar usu\303\241rios", nullptr));
        buttonUsuarioSwitch2->setText(QCoreApplication::translate("formUsuario", "USU\303\201RIO 2", nullptr));
        buttonBack->setText(QCoreApplication::translate("formUsuario", "Voltar a tela de in\303\255cio", nullptr));
        label->setText(QCoreApplication::translate("formUsuario", "MEU CENTAVO", nullptr));
        buttonUsuarioSwitch3->setText(QCoreApplication::translate("formUsuario", "USU\303\201RIO 3", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("formUsuario", "Adicionar novo usu\303\241rio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formUsuario: public Ui_formUsuario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMUSUARIO_H
