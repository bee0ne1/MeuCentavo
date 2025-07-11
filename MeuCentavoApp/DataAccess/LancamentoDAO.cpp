#include "LancamentoDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>


LancamentoDAO::LancamentoDAO(QSqlDatabase db, QObject *parent)
    : QObject(parent), m_db(db)
{

}

bool LancamentoDAO::adicionarLancamento(const Lancamento& lancamento)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO lancamentos (descricao, valor, data_lancamento, tipo, id_usuario) "
                  "VALUES (:descricao, :valor, :data, :tipo, :id_usuario)");

    query.bindValue(":descricao", lancamento.descricao);
    query.bindValue(":valor", lancamento.valor);
    // Convertemos o QDate para o formato de texto que o SQLite entende
    query.bindValue(":data", lancamento.data_lancamento.toString(Qt::ISODate));
    query.bindValue(":tipo", lancamento.tipo);
    query.bindValue(":id_usuario", lancamento.id_usuario);

    if (!query.exec()) {
        qDebug() << "Erro ao adicionar lançamento:" << query.lastError().text();
        return false;
    }

    return true;
}

double LancamentoDAO::obterSomaPorTipoNoMes(int usuarioId, const QString& tipo, int mes, int ano)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT SUM(valor) FROM lancamentos WHERE id_usuario = :id "
                  "AND tipo = :tipo "
                  "AND strftime('%m', data_lancamento) = :mes "
                  "AND strftime('%Y', data_lancamento) = :ano");

    query.bindValue(":id", usuarioId);
    query.bindValue(":tipo", tipo);
    // Formata o mês e ano para texto com o preenchimento de zeros correto
    query.bindValue(":mes", QString("%1").arg(mes, 2, 10, QChar('0')));
    query.bindValue(":ano", QString::number(ano));

    if (query.exec() && query.next()) {
        // .value(0) pega a primeira coluna do resultado (o SUM(valor))
        return query.value(0).toDouble();
    }
    return 0.0;
}

QVector<Lancamento> LancamentoDAO::obterLancamentosRecentes(int usuarioId, int limite)
{
    QVector<Lancamento> lancamentos;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM lancamentos WHERE id_usuario = :id "
                  "ORDER BY data_lancamento DESC, id DESC LIMIT :limite");

    query.bindValue(":id", usuarioId);
    query.bindValue(":limite", limite);

    if (query.exec()) {
        while (query.next()) {
            Lancamento l;
            l.id = query.value("id").toInt();
            l.descricao = query.value("descricao").toString();
            l.valor = query.value("valor").toDouble();
            l.data_lancamento = QDate::fromString(query.value("data_lancamento").toString(), Qt::ISODate);
            l.tipo = query.value("tipo").toString();
            l.id_usuario = query.value("id_usuario").toInt();
            // Adicione id_categoria e id_conta aqui se já as tiver
            lancamentos.append(l);
        }
    }
    return lancamentos;
}

QVector<Lancamento> LancamentoDAO::obterTodosLancamentosPorUsuario(int usuarioId)
{
    // Cria o vetor que será retornado
    QVector<Lancamento> listaLancamentos;
    QSqlQuery query(m_db);

    // Prepara a query SQL para buscar todos os lançamentos de um usuário específico,
    // ordenando pelos mais recentes primeiro.
    query.prepare("SELECT * FROM lancamentos WHERE id_usuario = :id_usuario ORDER BY data_lancamento DESC, id DESC");
    query.bindValue(":id_usuario", usuarioId);

    if (!query.exec()) {
        qDebug() << "Erro ao obter todos os lançamentos do usuário:" << query.lastError().text();
        return listaLancamentos; // Retorna a lista vazia em caso de erro
    }

    // Itera sobre cada linha que o banco de dados retornou
    while (query.next()) {
        Lancamento l; // Cria uma struct temporária

        // Preenche a struct com os dados da linha atual
        l.id = query.value("id").toInt();
        l.descricao = query.value("descricao").toString();
        l.valor = query.value("valor").toDouble();
        // Converte a data do formato de texto 'YYYY-MM-DD' para QDate
        l.data_lancamento = QDate::fromString(query.value("data_lancamento").toString(), Qt::ISODate);
        l.tipo = query.value("tipo").toString();
        l.id_usuario = query.value("id_usuario").toInt();

        // Se você já adicionou as colunas de categoria/conta, adicione-as aqui:
        // l.id_categoria = query.value("id_categoria").toInt();
        // l.id_conta = query.value("id_conta").toInt();

        // Adiciona o lançamento preenchido à nossa lista
        listaLancamentos.append(l);
    }

    // Retorna a lista com todos os lançamentos encontrados
    return listaLancamentos;
}