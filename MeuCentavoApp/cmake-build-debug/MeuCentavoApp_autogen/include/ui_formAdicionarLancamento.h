/********************************************************************************
** Form generated from reading UI file 'formAdicionarLancamento.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMADICIONARLANCAMENTO_H
#define UI_FORMADICIONARLANCAMENTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_formAdicionarLancamento
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QDoubleSpinBox *spinBoxValor;
    QLineEdit *lineEditDescricao;
    QLabel *label_3;
    QLabel *label;
    QComboBox *comboBoxTipo;
    QDateEdit *dateEditData;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonSalvar;
    QPushButton *buttonCancelar;

    void setupUi(QDialog *formAdicionarLancamento)
    {
        if (formAdicionarLancamento->objectName().isEmpty())
            formAdicionarLancamento->setObjectName("formAdicionarLancamento");
        formAdicionarLancamento->resize(603, 457);
        horizontalLayout_2 = new QHBoxLayout(formAdicionarLancamento);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(formAdicionarLancamento);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spinBoxValor = new QDoubleSpinBox(formAdicionarLancamento);
        spinBoxValor->setObjectName("spinBoxValor");

        gridLayout->addWidget(spinBoxValor, 1, 1, 1, 1);

        lineEditDescricao = new QLineEdit(formAdicionarLancamento);
        lineEditDescricao->setObjectName("lineEditDescricao");

        gridLayout->addWidget(lineEditDescricao, 0, 1, 1, 1);

        label_3 = new QLabel(formAdicionarLancamento);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(formAdicionarLancamento);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxTipo = new QComboBox(formAdicionarLancamento);
        comboBoxTipo->setObjectName("comboBoxTipo");

        gridLayout->addWidget(comboBoxTipo, 5, 1, 1, 1);

        dateEditData = new QDateEdit(formAdicionarLancamento);
        dateEditData->setObjectName("dateEditData");

        gridLayout->addWidget(dateEditData, 2, 1, 1, 1);

        label_4 = new QLabel(formAdicionarLancamento);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_4, 5, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        buttonSalvar = new QPushButton(formAdicionarLancamento);
        buttonSalvar->setObjectName("buttonSalvar");

        horizontalLayout->addWidget(buttonSalvar);

        buttonCancelar = new QPushButton(formAdicionarLancamento);
        buttonCancelar->setObjectName("buttonCancelar");

        horizontalLayout->addWidget(buttonCancelar);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(formAdicionarLancamento);

        QMetaObject::connectSlotsByName(formAdicionarLancamento);
    } // setupUi

    void retranslateUi(QDialog *formAdicionarLancamento)
    {
        formAdicionarLancamento->setWindowTitle(QCoreApplication::translate("formAdicionarLancamento", "formAdicionarLancamentos", nullptr));
        label_2->setText(QCoreApplication::translate("formAdicionarLancamento", "Valor", nullptr));
        label_3->setText(QCoreApplication::translate("formAdicionarLancamento", "Data de Lan\303\247amento", nullptr));
        label->setText(QCoreApplication::translate("formAdicionarLancamento", "Descri\303\247\303\243o", nullptr));
        label_4->setText(QCoreApplication::translate("formAdicionarLancamento", "Tipo", nullptr));
        buttonSalvar->setText(QCoreApplication::translate("formAdicionarLancamento", "Salvar", nullptr));
        buttonCancelar->setText(QCoreApplication::translate("formAdicionarLancamento", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formAdicionarLancamento: public Ui_formAdicionarLancamento {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMADICIONARLANCAMENTO_H
