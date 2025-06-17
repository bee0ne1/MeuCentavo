#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMainWindow>
#include "ui_interfaceMeuCentavo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file("Designer/metro.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        app.setStyleSheet(style);
    }

    QMainWindow mainWindow;
    Ui::MainWindow ui;
    ui.setupUi(&mainWindow);

    mainWindow.show();
    return app.exec();
}
