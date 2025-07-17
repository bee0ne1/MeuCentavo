/********************************************************************************
** Form generated from reading UI file 'formMainDashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMAINDASHBOARD_H
#define UI_FORMMAINDASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formMainDashboard
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QWidget *menuContainer;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonHome;
    QPushButton *buttonLancamentos;
    QPushButton *buttonRelatorios;
    QPushButton *buttonConfiguracoes;
    QPushButton *buttonSwitchUsuario;
    QStackedWidget *stackedWidgetConteudo;
    QWidget *page;
    QWidget *page_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *formMainDashboard)
    {
        if (formMainDashboard->objectName().isEmpty())
            formMainDashboard->setObjectName("formMainDashboard");
        formMainDashboard->resize(874, 688);
        centralwidget = new QWidget(formMainDashboard);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        menuContainer = new QWidget(centralwidget);
        menuContainer->setObjectName("menuContainer");
        horizontalLayout_2 = new QHBoxLayout(menuContainer);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        buttonHome = new QPushButton(menuContainer);
        buttonHome->setObjectName("buttonHome");

        verticalLayout->addWidget(buttonHome);

        buttonLancamentos = new QPushButton(menuContainer);
        buttonLancamentos->setObjectName("buttonLancamentos");

        verticalLayout->addWidget(buttonLancamentos);

        buttonRelatorios = new QPushButton(menuContainer);
        buttonRelatorios->setObjectName("buttonRelatorios");

        verticalLayout->addWidget(buttonRelatorios);

        buttonConfiguracoes = new QPushButton(menuContainer);
        buttonConfiguracoes->setObjectName("buttonConfiguracoes");

        verticalLayout->addWidget(buttonConfiguracoes);

        buttonSwitchUsuario = new QPushButton(menuContainer);
        buttonSwitchUsuario->setObjectName("buttonSwitchUsuario");
        buttonSwitchUsuario->setMinimumSize(QSize(200, 0));
        buttonSwitchUsuario->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(buttonSwitchUsuario);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout->addWidget(menuContainer);

        stackedWidgetConteudo = new QStackedWidget(centralwidget);
        stackedWidgetConteudo->setObjectName("stackedWidgetConteudo");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidgetConteudo->sizePolicy().hasHeightForWidth());
        stackedWidgetConteudo->setSizePolicy(sizePolicy);
        page = new QWidget();
        page->setObjectName("page");
        stackedWidgetConteudo->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetConteudo->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidgetConteudo);

        horizontalLayout->setStretch(1, 1);

        horizontalLayout_3->addLayout(horizontalLayout);

        formMainDashboard->setCentralWidget(centralwidget);
        menubar = new QMenuBar(formMainDashboard);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 874, 30));
        formMainDashboard->setMenuBar(menubar);
        statusbar = new QStatusBar(formMainDashboard);
        statusbar->setObjectName("statusbar");
        formMainDashboard->setStatusBar(statusbar);

        retranslateUi(formMainDashboard);

        stackedWidgetConteudo->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(formMainDashboard);
    } // setupUi

    void retranslateUi(QMainWindow *formMainDashboard)
    {
        formMainDashboard->setWindowTitle(QCoreApplication::translate("formMainDashboard", "formMainDashboard", nullptr));
        buttonHome->setText(QCoreApplication::translate("formMainDashboard", "Home", nullptr));
        buttonLancamentos->setText(QCoreApplication::translate("formMainDashboard", "Lan\303\247amentos", nullptr));
        buttonRelatorios->setText(QCoreApplication::translate("formMainDashboard", "Relat\303\263rios", nullptr));
        buttonConfiguracoes->setText(QCoreApplication::translate("formMainDashboard", "Configura\303\247\303\265es", nullptr));
        buttonSwitchUsuario->setText(QCoreApplication::translate("formMainDashboard", "Trocar Usu\303\241rio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formMainDashboard: public Ui_formMainDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMAINDASHBOARD_H
