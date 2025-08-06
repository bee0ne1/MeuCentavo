/********************************************************************************
** Form generated from reading UI file 'pageHome.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEHOME_H
#define UI_PAGEHOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pageHome
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *labelValorReceitas;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *labelValorDespesas;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QLabel *labelSaldoMes;
    QHBoxLayout *QHBoxGraficos;
    QVBoxLayout *layoutGraficoResumo;
    QVBoxLayout *layoutGraficoPatrimonio;
    QTableWidget *tabelaLancamentosRecentes;

    void setupUi(QWidget *pageHome)
    {
        if (pageHome->objectName().isEmpty())
            pageHome->setObjectName("pageHome");
        pageHome->resize(916, 759);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pageHome->sizePolicy().hasHeightForWidth());
        pageHome->setSizePolicy(sizePolicy);
        pageHome->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 88, 255)"));
        horizontalLayout_2 = new QHBoxLayout(pageHome);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox = new QGroupBox(pageHome);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        labelValorReceitas = new QLabel(groupBox);
        labelValorReceitas->setObjectName("labelValorReceitas");
        QFont font;
        font.setPointSize(16);
        labelValorReceitas->setFont(font);

        verticalLayout->addWidget(labelValorReceitas);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(pageHome);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        labelValorDespesas = new QLabel(groupBox_2);
        labelValorDespesas->setObjectName("labelValorDespesas");
        labelValorDespesas->setFont(font);

        verticalLayout_2->addWidget(labelValorDespesas);


        horizontalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(pageHome);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        labelSaldoMes = new QLabel(groupBox_3);
        labelSaldoMes->setObjectName("labelSaldoMes");
        labelSaldoMes->setFont(font);

        verticalLayout_3->addWidget(labelSaldoMes);


        horizontalLayout->addWidget(groupBox_3);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout);

        QHBoxGraficos = new QHBoxLayout();
        QHBoxGraficos->setObjectName("QHBoxGraficos");
        layoutGraficoResumo = new QVBoxLayout();
        layoutGraficoResumo->setObjectName("layoutGraficoResumo");

        QHBoxGraficos->addLayout(layoutGraficoResumo);

        layoutGraficoPatrimonio = new QVBoxLayout();
        layoutGraficoPatrimonio->setObjectName("layoutGraficoPatrimonio");

        QHBoxGraficos->addLayout(layoutGraficoPatrimonio);


        verticalLayout_4->addLayout(QHBoxGraficos);

        tabelaLancamentosRecentes = new QTableWidget(pageHome);
        if (tabelaLancamentosRecentes->columnCount() < 5)
            tabelaLancamentosRecentes->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tabelaLancamentosRecentes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tabelaLancamentosRecentes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tabelaLancamentosRecentes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tabelaLancamentosRecentes->setObjectName("tabelaLancamentosRecentes");
        tabelaLancamentosRecentes->setMaximumSize(QSize(16777215, 150));
        tabelaLancamentosRecentes->setColumnCount(5);

        verticalLayout_4->addWidget(tabelaLancamentosRecentes);

        verticalLayout_4->setStretch(1, 1);

        horizontalLayout_2->addLayout(verticalLayout_4);


        retranslateUi(pageHome);

        QMetaObject::connectSlotsByName(pageHome);
    } // setupUi

    void retranslateUi(QWidget *pageHome)
    {
        pageHome->setWindowTitle(QCoreApplication::translate("pageHome", "pageHome", nullptr));
        groupBox->setTitle(QCoreApplication::translate("pageHome", "Receitas Do M\303\252s", nullptr));
        label->setText(QCoreApplication::translate("pageHome", "TextLabel", nullptr));
        labelValorReceitas->setText(QCoreApplication::translate("pageHome", "R$ 0,00", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("pageHome", "Despesas Do M\303\252s", nullptr));
        label_2->setText(QCoreApplication::translate("pageHome", "TextLabel", nullptr));
        labelValorDespesas->setText(QCoreApplication::translate("pageHome", "R$ 0,00", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("pageHome", "Saldo do M\303\252s", nullptr));
        label_4->setText(QCoreApplication::translate("pageHome", "TextLabel", nullptr));
        labelSaldoMes->setText(QCoreApplication::translate("pageHome", "R$ 0,00", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tabelaLancamentosRecentes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("pageHome", "Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tabelaLancamentosRecentes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("pageHome", "Descri\303\247\303\243o", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tabelaLancamentosRecentes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("pageHome", "Valor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pageHome: public Ui_pageHome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEHOME_H
