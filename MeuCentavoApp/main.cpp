#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include "Designer/formMain.h"  // Inclui a sua nova tela principal
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Carrega o estilo (QSS)
    QFile file("Designer/metro.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        app.setStyleSheet(style);
    }

    // Conexão com o banco de dados
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("gestaofinanceira");
    db.setUserName("bruno");
    db.setPassword("8243");

    if (!db.open()) {
        qDebug() << "Erro ao conectar ao banco de dados:" << db.lastError().text();
        return -1;
    }

    qDebug() << "Conexão com o banco de dados estabelecida com sucesso!";


    formMain janela(db);
    janela.show();

    return app.exec();
}
