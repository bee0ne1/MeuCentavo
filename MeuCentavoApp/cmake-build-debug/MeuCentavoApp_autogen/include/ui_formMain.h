/********************************************************************************
** Form generated from reading UI file 'formMain.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMAIN_H
#define UI_FORMMAIN_H

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

class Ui_formMain
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

    void setupUi(QMainWindow *formMain)
    {
        if (formMain->objectName().isEmpty())
            formMain->setObjectName("formMain");
        formMain->resize(800, 600);
        formMain->setMinimumSize(QSize(800, 600));
        formMain->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setKerning(true);
        formMain->setFont(font);
        formMain->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        formMain->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 88, 255)"));
        formMain->setAnimated(true);
        centralwidget = new QWidget(formMain);
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

        formMain->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(formMain);
        statusbar->setObjectName("statusbar");
        formMain->setStatusBar(statusbar);

        retranslateUi(formMain);

        QMetaObject::connectSlotsByName(formMain);
    } // setupUi

    void retranslateUi(QMainWindow *formMain)
    {
        formMain->setWindowTitle(QCoreApplication::translate("formMain", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("formMain", "MEU CENTAVO", nullptr));
        buttonAppAcess->setText(QCoreApplication::translate("formMain", "USU\303\201RIO ", nullptr));
        buttonExit->setText(QCoreApplication::translate("formMain", "Sair", nullptr));
        buttonSwitchUsuario->setText(QCoreApplication::translate("formMain", "Trocar Usu\303\241rio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formMain: public Ui_formMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMAIN_H
