//
// Created by bruno on 07/07/25.
//

#ifndef PASSWORDFORMHELPER_H
#define PASSWORDFORMHELPER_H

#include <QObject>

// Forward declarations para os widgets que vamos usar
class QLineEdit;
class QPushButton;

class PasswordFormHelper : public QObject
{
    Q_OBJECT
public:
    // O construtor recebe os ponteiros para os widgets que ele vai controlar
    explicit PasswordFormHelper(QLineEdit *passwordField, QPushButton *toggleButton, QObject *parent = nullptr);

private slots:
    void togglePasswordVisibility();

private:
    QLineEdit *m_passwordField;
    QPushButton *m_toggleButton;
};

#endif // PASSWORDFORMHELPER_H