/********************************************************************************
** Form generated from reading UI file 'formExcluirUsuario.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMEXCLUIRUSUARIO_H
#define UI_FORMEXCLUIRUSUARIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formExcluirUsuario
{
public:
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *layoutUsuariosExcluir;
    QPushButton *buttonVoltar;

    void setupUi(QWidget *formExcluirUsuario)
    {
        if (formExcluirUsuario->objectName().isEmpty())
            formExcluirUsuario->setObjectName("formExcluirUsuario");
        formExcluirUsuario->resize(800, 600);
        formExcluirUsuario->setMinimumSize(QSize(800, 600));
        formExcluirUsuario->setMaximumSize(QSize(800, 600));
        formExcluirUsuario->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 88, 255)"));
        label = new QLabel(formExcluirUsuario);
        label->setObjectName("label");
        label->setGeometry(QRect(150, 20, 520, 68));
        label->setMaximumSize(QSize(800, 100));
        QFont font;
        font.setFamilies({QString::fromUtf8("Noto Sans Arabic Cond Light")});
        font.setPointSize(24);
        font.setWeight(QFont::Light);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font: 300 24pt \"Noto Sans Arabic Cond Light\";"));
        label->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);
        horizontalLayoutWidget = new QWidget(formExcluirUsuario);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(260, 190, 321, 101));
        layoutUsuariosExcluir = new QHBoxLayout(horizontalLayoutWidget);
        layoutUsuariosExcluir->setObjectName("layoutUsuariosExcluir");
        layoutUsuariosExcluir->setContentsMargins(0, 0, 0, 0);
        buttonVoltar = new QPushButton(formExcluirUsuario);
        buttonVoltar->setObjectName("buttonVoltar");
        buttonVoltar->setGeometry(QRect(360, 490, 88, 34));

        retranslateUi(formExcluirUsuario);

        QMetaObject::connectSlotsByName(formExcluirUsuario);
    } // setupUi

    void retranslateUi(QWidget *formExcluirUsuario)
    {
        formExcluirUsuario->setWindowTitle(QCoreApplication::translate("formExcluirUsuario", "formExcluirUsuario", nullptr));
        label->setText(QCoreApplication::translate("formExcluirUsuario", "MEU CENTAVO", nullptr));
        buttonVoltar->setText(QCoreApplication::translate("formExcluirUsuario", "Voltar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formExcluirUsuario: public Ui_formExcluirUsuario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMEXCLUIRUSUARIO_H
