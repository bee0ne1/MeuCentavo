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
#include <QtWidgets/QPushButton>
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
    QPushButton *buttonViewPassword;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_5;
    QLineEdit *lineEditUsuario;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *lineEditSenha;
    QPushButton *buttonGravarUsuario;
    QPushButton *buttonCancelar;

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
        label_4->setMaximumSize(QSize(70, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond")});
        font.setPointSize(14);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_4, 4, 1, 1, 1);

        buttonViewPassword = new QPushButton(formCadastro);
        buttonViewPassword->setObjectName("buttonViewPassword");
        buttonViewPassword->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(buttonViewPassword, 5, 3, 1, 1);

        label_3 = new QLabel(formCadastro);
        label_3->setObjectName("label_3");
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        lineEdit = new QLineEdit(formCadastro);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setEnabled(false);

        gridLayout->addWidget(lineEdit, 3, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 6, 2, 1, 1);

        label_5 = new QLabel(formCadastro);
        label_5->setObjectName("label_5");
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_5, 5, 1, 1, 1);

        lineEditUsuario = new QLineEdit(formCadastro);
        lineEditUsuario->setObjectName("lineEditUsuario");

        gridLayout->addWidget(lineEditUsuario, 4, 2, 1, 1);

        label = new QLabel(formCadastro);
        label->setObjectName("label");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond")});
        font1.setPointSize(24);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 11, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 5, 4, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 1);

        label_2 = new QLabel(formCadastro);
        label_2->setObjectName("label_2");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond")});
        font2.setPointSize(20);
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_2, 2, 2, 1, 1);

        lineEditSenha = new QLineEdit(formCadastro);
        lineEditSenha->setObjectName("lineEditSenha");
        lineEditSenha->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(lineEditSenha, 5, 2, 1, 1);

        buttonGravarUsuario = new QPushButton(formCadastro);
        buttonGravarUsuario->setObjectName("buttonGravarUsuario");
        buttonGravarUsuario->setEnabled(false);

        gridLayout->addWidget(buttonGravarUsuario, 8, 2, 1, 1);

        buttonCancelar = new QPushButton(formCadastro);
        buttonCancelar->setObjectName("buttonCancelar");
        buttonCancelar->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(buttonCancelar, 9, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        QWidget::setTabOrder(lineEdit, lineEditUsuario);
        QWidget::setTabOrder(lineEditUsuario, lineEditSenha);

        retranslateUi(formCadastro);

        QMetaObject::connectSlotsByName(formCadastro);
    } // setupUi

    void retranslateUi(QWidget *formCadastro)
    {
        formCadastro->setWindowTitle(QCoreApplication::translate("formCadastro", "formCadastro", nullptr));
        label_4->setText(QCoreApplication::translate("formCadastro", "USU\303\201RIO", nullptr));
        buttonViewPassword->setText(QCoreApplication::translate("formCadastro", "Visualizar", nullptr));
        label_3->setText(QCoreApplication::translate("formCadastro", "C\303\223DIGO", nullptr));
        label_5->setText(QCoreApplication::translate("formCadastro", "SENHA", nullptr));
        label->setText(QCoreApplication::translate("formCadastro", "MEU CENTAVO", nullptr));
        label_2->setText(QCoreApplication::translate("formCadastro", "CADASTRO", nullptr));
        buttonGravarUsuario->setText(QCoreApplication::translate("formCadastro", "Gravar", nullptr));
        buttonCancelar->setText(QCoreApplication::translate("formCadastro", "Cancelar cadastro", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formCadastro: public Ui_formCadastro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCADASTRO_H
