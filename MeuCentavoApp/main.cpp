#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include "Designer/formInicio.h"
#include "Designer/FormsLogin/formBoasVindas.h"
#include "DataAccess/UsuarioDAO.h"
#include <QMessageBox>
#include <QSqlQuery>



void configurarBancoInicial(QSqlDatabase& db)
{
    QSqlQuery query(db);
    // A cláusula "IF NOT EXISTS" é crucial. Ela garante que o comando só
    // fará algo se a tabela realmente não existir.
    QString criarTabelaUsuario = "CREATE TABLE IF NOT EXISTS usuario ("
                                 "user_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "user_usuario TEXT NOT NULL UNIQUE, "
                                 "user_password TEXT NOT NULL"
                                 ");";

    if (!query.exec(criarTabelaUsuario)) {
        qDebug() << "Erro ao criar tabela usuario:" << query.lastError();
    } else {
        qDebug() << "Tabela 'usuario' verificada/criada com sucesso.";
    }
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("meucentavo.db");

    if (!db.open()) {
        qDebug() << "Erro crítico ao abrir/criar banco de dados:" << db.lastError();
        return -1;
    }

    configurarBancoInicial(db);

    // verifica se ha usuarios criados,abre uma tela de boas vindas caso nao
    UsuarioDAO dao(db);
    if (dao.existemUsuarios()) {
        // Se já existem usuários, abre a tela principal normal.
        qDebug() << "Usuários encontrados. Abrindo formMain.";
        formInicio *w = new formInicio(db);
        w->show();
    } else {
        // Se não existem usuários, abre a tela de boas-vindas.
        qDebug() << "Nenhum usuário encontrado. Abrindo formBoasVindas.";
        formBoasVindas *w = new formBoasVindas(db);
        w->show();
    }
    return app.exec();

}
