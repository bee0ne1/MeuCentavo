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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formMain
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *buttonCadastro;
    QMenuBar *menubar;
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

        verticalLayout->addWidget(label);

        buttonCadastro = new QPushButton(centralwidget);
        buttonCadastro->setObjectName("buttonCadastro");

        verticalLayout->addWidget(buttonCadastro);

        formMain->setCentralWidget(centralwidget);
        menubar = new QMenuBar(formMain);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 30));
        formMain->setMenuBar(menubar);
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
        buttonCadastro->setText(QCoreApplication::translate("formMain", "Cadastro", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formMain: public Ui_formMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMAIN_H
