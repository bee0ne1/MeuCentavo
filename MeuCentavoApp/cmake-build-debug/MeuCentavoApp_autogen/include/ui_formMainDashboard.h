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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formMainDashboard
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *Cabecalho;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboPerfisAtivos;
    QSpacerItem *horizontalSpacer;
    QLabel *labelNomeUsuario;
    QPushButton *buttonSwitchUsuario;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *menuContainer;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonHome;
    QPushButton *buttonLancamentos;
    QPushButton *buttonRelatorios;
    QPushButton *buttonMetas;
    QPushButton *buttonInvestimentos;
    QPushButton *buttonDividas;
    QPushButton *buttonConfiguracoes;
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
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        Cabecalho = new QWidget(centralwidget);
        Cabecalho->setObjectName("Cabecalho");
        horizontalLayout_3 = new QHBoxLayout(Cabecalho);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(Cabecalho);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        label_2 = new QLabel(Cabecalho);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        comboPerfisAtivos = new QComboBox(Cabecalho);
        comboPerfisAtivos->setObjectName("comboPerfisAtivos");

        horizontalLayout_3->addWidget(comboPerfisAtivos);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        labelNomeUsuario = new QLabel(Cabecalho);
        labelNomeUsuario->setObjectName("labelNomeUsuario");

        horizontalLayout_3->addWidget(labelNomeUsuario);

        buttonSwitchUsuario = new QPushButton(Cabecalho);
        buttonSwitchUsuario->setObjectName("buttonSwitchUsuario");
        buttonSwitchUsuario->setMinimumSize(QSize(200, 0));
        buttonSwitchUsuario->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(buttonSwitchUsuario);


        verticalLayout_2->addWidget(Cabecalho);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        menuContainer = new QWidget(widget);
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

        buttonMetas = new QPushButton(menuContainer);
        buttonMetas->setObjectName("buttonMetas");

        verticalLayout->addWidget(buttonMetas);

        buttonInvestimentos = new QPushButton(menuContainer);
        buttonInvestimentos->setObjectName("buttonInvestimentos");

        verticalLayout->addWidget(buttonInvestimentos);

        buttonDividas = new QPushButton(menuContainer);
        buttonDividas->setObjectName("buttonDividas");

        verticalLayout->addWidget(buttonDividas);

        buttonConfiguracoes = new QPushButton(menuContainer);
        buttonConfiguracoes->setObjectName("buttonConfiguracoes");

        verticalLayout->addWidget(buttonConfiguracoes);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout_4->addWidget(menuContainer);

        stackedWidgetConteudo = new QStackedWidget(widget);
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

        horizontalLayout_4->addWidget(stackedWidgetConteudo);


        verticalLayout_2->addWidget(widget);

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
        label->setText(QCoreApplication::translate("formMainDashboard", "Meu Centavo (logo)", nullptr));
        label_2->setText(QCoreApplication::translate("formMainDashboard", "Perfil: ", nullptr));
        labelNomeUsuario->setText(QCoreApplication::translate("formMainDashboard", "nome usuario", nullptr));
        buttonSwitchUsuario->setText(QCoreApplication::translate("formMainDashboard", "Trocar Usu\303\241rio / Sair", nullptr));
        buttonHome->setText(QCoreApplication::translate("formMainDashboard", "Home", nullptr));
        buttonLancamentos->setText(QCoreApplication::translate("formMainDashboard", "Lan\303\247amentos", nullptr));
        buttonRelatorios->setText(QCoreApplication::translate("formMainDashboard", "Relat\303\263rios", nullptr));
        buttonMetas->setText(QCoreApplication::translate("formMainDashboard", "Metas", nullptr));
        buttonInvestimentos->setText(QCoreApplication::translate("formMainDashboard", "Investimentos", nullptr));
        buttonDividas->setText(QCoreApplication::translate("formMainDashboard", "D\303\255vidas", nullptr));
        buttonConfiguracoes->setText(QCoreApplication::translate("formMainDashboard", "Configura\303\247\303\265es", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formMainDashboard: public Ui_formMainDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMAINDASHBOARD_H
