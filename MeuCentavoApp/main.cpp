#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMainWindow>
#include "ui_interfaceMeuCentavo.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>


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
    db.setDatabaseName("MeuCentavoDB");  // Altere para o nome real do banco
    db.setUserName("root");        // Altere para seu usuário
    db.setPassword("8243");          // Altere para sua senha

    if (!db.open()) {
        qDebug() << "Erro ao conectar ao banco de dados:" << db.lastError().text();
        return -1;
    }

    qDebug() << "Conexão com o banco de dados estabelecida com sucesso!";

    // Cria e exibe a janela principal
    QMainWindow mainWindow;
    Ui::MainWindow ui;
    ui.setupUi(&mainWindow);
    mainWindow.show();

    // Inicia o loop da aplicação
    return app.exec();
}
