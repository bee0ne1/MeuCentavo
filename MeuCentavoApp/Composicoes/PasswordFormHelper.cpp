//
// Created by bruno on 07/07/25.
//

// PasswordFormHelper.cpp
#include "PasswordFormHelper.h"
#include <QLineEdit>
#include <QPushButton>

PasswordFormHelper::PasswordFormHelper(QLineEdit *passwordField, QPushButton *toggleButton, QObject *parent)
    : QObject(parent), m_passwordField(passwordField), m_toggleButton(toggleButton)
{
    if (m_passwordField && m_toggleButton) {
        // A lógica de conexão agora vive aqui dentro!
        connect(m_toggleButton, &QPushButton::clicked, this, &PasswordFormHelper::togglePasswordVisibility);
    }
}

void PasswordFormHelper::togglePasswordVisibility()
{
    if (!m_passwordField) return;

    bool isHidden = m_passwordField->echoMode() == QLineEdit::Password;
    m_passwordField->setEchoMode(isHidden ? QLineEdit::Normal : QLineEdit::Password);
    // Opcional: Mudar o texto do botão para dar feedback
    m_toggleButton->setText(isHidden ? "Esconder" : "Visualizar");
}
