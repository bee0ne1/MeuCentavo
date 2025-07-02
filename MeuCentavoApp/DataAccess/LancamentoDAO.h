//
// Created by bruno on 29/06/25.
//

#ifndef LANCAMENTODAO_H
#define LANCAMENTODAO_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
#include "Modelo/Lancamento.h" // Inclui a struct que acabamos de criar

class LancamentoDAO : public QObject {
    Q_OBJECT
public:
    // O construtor recebe a conexão com o banco de dados já aberta
    explicit LancamentoDAO(QSqlDatabase db, QObject *parent = nullptr);

    // Método para adicionar um novo lançamento no banco
    bool adicionarLancamento(const Lancamento& lancamento);

    // Método para obter todos os lançamentos do banco
    QVector<Lancamento> obterTodosLancamentos();

    // Você pode adicionar outros métodos aqui depois:
    // bool atualizarLancamento(const Lancamento& lancamento);
    // bool removerLancamento(int id);

private:
    QSqlDatabase m_db; // Armazena a instância da conexão com o banco
};

#endif //MEUCENTAVOAPP_LANCAMENTODAO_H

