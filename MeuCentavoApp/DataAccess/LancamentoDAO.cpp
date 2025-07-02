#include "LancamentoDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


LancamentoDAO::LancamentoDAO(QSqlDatabase db, QObject *parent)
    : QObject(parent), m_db(db) {}

// Implementação para obter os dados (sua pergunta principal)
QVector<Lancamento> LancamentoDAO::obterTodosLancamentos() {
    QVector<Lancamento> lancamentos;

    // QSqlQuery é o objeto usado para executar comandos SQL
    QSqlQuery query(m_db);

    // Preparamos o comando SQL para evitar injeção de SQL e melhorar a performance
    // Substitua 'sua_tabela_lancamentos' pelo nome real da sua tabela
    QString sql = "SELECT id, descricao, valor, data, tipo FROM sua_tabela_lancamentos ORDER BY data DESC";

    if (!query.prepare(sql)) {
        qDebug() << "Erro ao preparar a query de seleção:" << query.lastError().text();
        return lancamentos; // Retorna lista vazia em caso de erro
    }

    // Executa a query
    if (!query.exec()) {
        qDebug() << "Erro ao executar a query de seleção:" << query.lastError().text();
        return lancamentos;
    }

    // Itera sobre os resultados
    while (query.next()) {
        Lancamento lanc;
        lanc.id = query.value("id").toInt();
        lanc.descricao = query.value("descricao").toString();
        lanc.valor = query.value("valor").toDouble();
        lanc.data = query.value("data").toDate();
        lanc.tipo = query.value("tipo").toString();

        lancamentos.append(lanc);
    }

    return lancamentos;
}


// Implementação para adicionar um novo registro
bool LancamentoDAO::adicionarLancamento(const Lancamento& lancamento) {
    QSqlQuery query(m_db);

    // Substitua 'sua_tabela_lancamentos' pelo nome real da sua tabela
    QString sql = "INSERT INTO sua_tabela_lancamentos (descricao, valor, data, tipo) "
                  "VALUES (:descricao, :valor, :data, :tipo)";

    if (!query.prepare(sql)) {
        qDebug() << "Erro ao preparar a query de inserção:" << query.lastError().text();
        return false;
    }

    // Substitui os "placeholders" pelos valores reais da struct
    query.bindValue(":descricao", lancamento.descricao);
    query.bindValue(":valor", lancamento.valor);
    query.bindValue(":data", lancamento.data);
    query.bindValue(":tipo", lancamento.tipo);

    if (!query.exec()) {
        qDebug() << "Erro ao executar a query de inserção:" << query.lastError().text();
        return false;
    }

    return true;
}
