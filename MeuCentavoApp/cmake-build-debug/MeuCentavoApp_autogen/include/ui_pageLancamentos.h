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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
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
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonAdicionarLancamento;
    QPushButton *buttonImportarExtrato;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *layoutFiltros;
    QLabel *label;
    QDateEdit *dateEditInicio;
    QLabel *label_2;
    QDateEdit *dateEditFim;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QComboBox *comboBoxConta;
    QPushButton *buttonFiltrar;
    QTableWidget *tabelaTodosLancamentos;

    void setupUi(QWidget *pageLancamentos)
    {
        if (pageLancamentos->objectName().isEmpty())
            pageLancamentos->setObjectName("pageLancamentos");
        pageLancamentos->resize(1008, 753);
        horizontalLayout_2 = new QHBoxLayout(pageLancamentos);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonAdicionarLancamento = new QPushButton(pageLancamentos);
        buttonAdicionarLancamento->setObjectName("buttonAdicionarLancamento");

        horizontalLayout->addWidget(buttonAdicionarLancamento);

        buttonImportarExtrato = new QPushButton(pageLancamentos);
        buttonImportarExtrato->setObjectName("buttonImportarExtrato");

        horizontalLayout->addWidget(buttonImportarExtrato);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        layoutFiltros = new QHBoxLayout();
        layoutFiltros->setObjectName("layoutFiltros");
        label = new QLabel(pageLancamentos);
        label->setObjectName("label");

        layoutFiltros->addWidget(label);

        dateEditInicio = new QDateEdit(pageLancamentos);
        dateEditInicio->setObjectName("dateEditInicio");

        layoutFiltros->addWidget(dateEditInicio);

        label_2 = new QLabel(pageLancamentos);
        label_2->setObjectName("label_2");

        layoutFiltros->addWidget(label_2);

        dateEditFim = new QDateEdit(pageLancamentos);
        dateEditFim->setObjectName("dateEditFim");

        layoutFiltros->addWidget(dateEditFim);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutFiltros->addItem(horizontalSpacer_3);

        label_3 = new QLabel(pageLancamentos);
        label_3->setObjectName("label_3");

        layoutFiltros->addWidget(label_3);

        comboBoxConta = new QComboBox(pageLancamentos);
        comboBoxConta->setObjectName("comboBoxConta");

        layoutFiltros->addWidget(comboBoxConta);

        buttonFiltrar = new QPushButton(pageLancamentos);
        buttonFiltrar->setObjectName("buttonFiltrar");

        layoutFiltros->addWidget(buttonFiltrar);


        gridLayout->addLayout(layoutFiltros, 1, 0, 1, 1);

        tabelaTodosLancamentos = new QTableWidget(pageLancamentos);
        if (tabelaTodosLancamentos->columnCount() < 6)
            tabelaTodosLancamentos->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tabelaTodosLancamentos->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tabelaTodosLancamentos->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tabelaTodosLancamentos->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tabelaTodosLancamentos->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tabelaTodosLancamentos->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tabelaTodosLancamentos->setObjectName("tabelaTodosLancamentos");
        tabelaTodosLancamentos->setColumnCount(6);

        gridLayout->addWidget(tabelaTodosLancamentos, 2, 0, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);


        retranslateUi(pageLancamentos);

        QMetaObject::connectSlotsByName(pageLancamentos);
    } // setupUi

    void retranslateUi(QWidget *pageLancamentos)
    {
        pageLancamentos->setWindowTitle(QCoreApplication::translate("pageLancamentos", "pageLancamentos", nullptr));
        buttonAdicionarLancamento->setText(QCoreApplication::translate("pageLancamentos", "Adicionar Novo Lan\303\247amento", nullptr));
        buttonImportarExtrato->setText(QCoreApplication::translate("pageLancamentos", "Importar Extrato (.CSV)", nullptr));
        label->setText(QCoreApplication::translate("pageLancamentos", "Per\303\255odo: ", nullptr));
        label_2->setText(QCoreApplication::translate("pageLancamentos", " at\303\251 ", nullptr));
        label_3->setText(QCoreApplication::translate("pageLancamentos", "Conta: ", nullptr));
        buttonFiltrar->setText(QCoreApplication::translate("pageLancamentos", "Filtrar", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tabelaTodosLancamentos->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("pageLancamentos", "Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tabelaTodosLancamentos->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("pageLancamentos", "Descri\303\247\303\243o", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tabelaTodosLancamentos->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("pageLancamentos", "Tipo", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tabelaTodosLancamentos->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("pageLancamentos", "Valor", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tabelaTodosLancamentos->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("pageLancamentos", "Excluir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pageLancamentos: public Ui_pageLancamentos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGELANCAMENTOS_H
