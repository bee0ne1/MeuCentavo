/********************************************************************************
** Form generated from reading UI file 'pageLancamentos.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGELANCAMENTOS_H
#define UI_PAGELANCAMENTOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pageLancamentos
{
public:
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QTableWidget *tabelaTodosLancamentos;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonAdicionarLancamento;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *pageLancamentos)
    {
        if (pageLancamentos->objectName().isEmpty())
            pageLancamentos->setObjectName("pageLancamentos");
        pageLancamentos->resize(1008, 753);
        horizontalLayout_2 = new QHBoxLayout(pageLancamentos);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        tabelaTodosLancamentos = new QTableWidget(pageLancamentos);
        if (tabelaTodosLancamentos->columnCount() < 5)
            tabelaTodosLancamentos->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tabelaTodosLancamentos->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tabelaTodosLancamentos->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tabelaTodosLancamentos->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tabelaTodosLancamentos->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tabelaTodosLancamentos->setObjectName("tabelaTodosLancamentos");
        tabelaTodosLancamentos->setColumnCount(5);

        gridLayout->addWidget(tabelaTodosLancamentos, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonAdicionarLancamento = new QPushButton(pageLancamentos);
        buttonAdicionarLancamento->setObjectName("buttonAdicionarLancamento");

        horizontalLayout->addWidget(buttonAdicionarLancamento);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);


        retranslateUi(pageLancamentos);

        QMetaObject::connectSlotsByName(pageLancamentos);
    } // setupUi

    void retranslateUi(QWidget *pageLancamentos)
    {
        pageLancamentos->setWindowTitle(QCoreApplication::translate("pageLancamentos", "pageLancamentos", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tabelaTodosLancamentos->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("pageLancamentos", "Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tabelaTodosLancamentos->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("pageLancamentos", "Descri\303\247\303\243o", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tabelaTodosLancamentos->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("pageLancamentos", "Tipo", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tabelaTodosLancamentos->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("pageLancamentos", "Valor", nullptr));
        buttonAdicionarLancamento->setText(QCoreApplication::translate("pageLancamentos", "Adicionar Novo Lan\303\247amento", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pageLancamentos: public Ui_pageLancamentos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGELANCAMENTOS_H
