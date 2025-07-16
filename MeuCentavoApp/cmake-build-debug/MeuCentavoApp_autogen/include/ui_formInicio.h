/********************************************************************************
** Form generated from reading UI file 'formInicio.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMINICIO_H
#define UI_FORMINICIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formInicio
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *buttonAppAcess;
    QPushButton *buttonExit;
    QPushButton *buttonSwitchUsuario;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *formInicio)
    {
        if (formInicio->objectName().isEmpty())
            formInicio->setObjectName("formInicio");
        formInicio->resize(800, 600);
        formInicio->setMinimumSize(QSize(800, 600));
        formInicio->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setKerning(true);
        formInicio->setFont(font);
        formInicio->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        formInicio->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 88, 255)"));
        formInicio->setAnimated(true);
        centralwidget = new QWidget(formInicio);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(800, 100));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond Light")});
        font1.setPointSize(24);
        font1.setWeight(QFont::Light);
        font1.setItalic(false);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("font: 300 24pt \"Noto Sans Arabic Cond Light\";"));
        label->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        buttonAppAcess = new QPushButton(centralwidget);
        buttonAppAcess->setObjectName("buttonAppAcess");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonAppAcess->sizePolicy().hasHeightForWidth());
        buttonAppAcess->setSizePolicy(sizePolicy);
        buttonAppAcess->setMinimumSize(QSize(200, 200));

        gridLayout->addWidget(buttonAppAcess, 3, 0, 1, 1);

        buttonExit = new QPushButton(centralwidget);
        buttonExit->setObjectName("buttonExit");
        buttonExit->setMinimumSize(QSize(200, 0));
        buttonExit->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(buttonExit, 6, 0, 1, 1);

        buttonSwitchUsuario = new QPushButton(centralwidget);
        buttonSwitchUsuario->setObjectName("buttonSwitchUsuario");
        buttonSwitchUsuario->setMinimumSize(QSize(200, 0));
        buttonSwitchUsuario->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(buttonSwitchUsuario, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 7, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 4, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        formInicio->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(formInicio);
        statusbar->setObjectName("statusbar");
        formInicio->setStatusBar(statusbar);

        retranslateUi(formInicio);

        QMetaObject::connectSlotsByName(formInicio);
    } // setupUi

    void retranslateUi(QMainWindow *formInicio)
    {
        formInicio->setWindowTitle(QCoreApplication::translate("formInicio", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("formInicio", "MEU CENTAVO", nullptr));
        buttonAppAcess->setText(QCoreApplication::translate("formInicio", "USU\303\201RIO ", nullptr));
        buttonExit->setText(QCoreApplication::translate("formInicio", "Sair", nullptr));
        buttonSwitchUsuario->setText(QCoreApplication::translate("formInicio", "Trocar Usu\303\241rio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formInicio: public Ui_formInicio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMINICIO_H
