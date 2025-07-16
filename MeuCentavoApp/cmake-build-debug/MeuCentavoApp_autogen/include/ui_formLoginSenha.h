/********************************************************************************
** Form generated from reading UI file 'formLoginSenha.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMLOGINSENHA_H
#define UI_FORMLOGINSENHA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formLoginSenha
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *cabecalho;
    QLabel *label;
    QLabel *labelPrompt;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_10;
    QLineEdit *lineEditSenha;
    QPushButton *buttonViewPassword;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *buttonEntrar;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *buttonCancelar;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *formLoginSenha)
    {
        if (formLoginSenha->objectName().isEmpty())
            formLoginSenha->setObjectName("formLoginSenha");
        formLoginSenha->resize(600, 400);
        formLoginSenha->setMaximumSize(QSize(600, 400));
        formLoginSenha->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 88, 255)"));
        horizontalLayout = new QHBoxLayout(formLoginSenha);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        cabecalho = new QVBoxLayout();
        cabecalho->setObjectName("cabecalho");
        label = new QLabel(formLoginSenha);
        label->setObjectName("label");
        label->setMaximumSize(QSize(800, 100));
        QFont font;
        font.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond Light")});
        font.setPointSize(24);
        font.setWeight(QFont::Light);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font: 300 24pt \"Noto Sans Arabic Cond Light\";"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        cabecalho->addWidget(label);

        labelPrompt = new QLabel(formLoginSenha);
        labelPrompt->setObjectName("labelPrompt");
        QFont font1;
        font1.setPointSize(20);
        labelPrompt->setFont(font1);
        labelPrompt->setAlignment(Qt::AlignmentFlag::AlignCenter);

        cabecalho->addWidget(labelPrompt);

        label_2 = new QLabel(formLoginSenha);
        label_2->setObjectName("label_2");
        QFont font2;
        font2.setPointSize(18);
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        cabecalho->addWidget(label_2);


        verticalLayout->addLayout(cabecalho);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        lineEditSenha = new QLineEdit(formLoginSenha);
        lineEditSenha->setObjectName("lineEditSenha");
        lineEditSenha->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_4->addWidget(lineEditSenha);

        buttonViewPassword = new QPushButton(formLoginSenha);
        buttonViewPassword->setObjectName("buttonViewPassword");

        horizontalLayout_4->addWidget(buttonViewPassword);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        horizontalLayout_4->setStretch(4, 1);

        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        buttonEntrar = new QPushButton(formLoginSenha);
        buttonEntrar->setObjectName("buttonEntrar");

        horizontalLayout_5->addWidget(buttonEntrar);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        buttonCancelar = new QPushButton(formLoginSenha);
        buttonCancelar->setObjectName("buttonCancelar");

        horizontalLayout_7->addWidget(buttonCancelar);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_7);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(formLoginSenha);

        QMetaObject::connectSlotsByName(formLoginSenha);
    } // setupUi

    void retranslateUi(QWidget *formLoginSenha)
    {
        formLoginSenha->setWindowTitle(QCoreApplication::translate("formLoginSenha", "formLoginSenha", nullptr));
        label->setText(QCoreApplication::translate("formLoginSenha", "MEU CENTAVO", nullptr));
        labelPrompt->setText(QCoreApplication::translate("formLoginSenha", "bemvindo", nullptr));
        label_2->setText(QCoreApplication::translate("formLoginSenha", "Confirme sua senha", nullptr));
        buttonViewPassword->setText(QCoreApplication::translate("formLoginSenha", "Visualizar", nullptr));
        buttonEntrar->setText(QCoreApplication::translate("formLoginSenha", "Entrar", nullptr));
        buttonCancelar->setText(QCoreApplication::translate("formLoginSenha", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formLoginSenha: public Ui_formLoginSenha {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMLOGINSENHA_H
