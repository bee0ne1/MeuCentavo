#ifndef CONTADAO_H
#define CONTADAO_H

#include <QObject>
#include <QVector>
#include "Modelo/Conta.h"
#include "Modelo/Categoria.h"

// Forward declarations
class QNetworkAccessManager;
class QNetworkReply;

class ContaDAO : public QObject
{
    Q_OBJECT
public:
    explicit ContaDAO(QObject *parent = nullptr);

    // MÉTODOS DE CONTAS
    void obterTodasContas(const QString& token);
    void adicionarConta(const Conta& conta, const QString& token);
    void editarConta(const Conta& conta, const QString& token);
    void excluirConta(int idConta, const QString& token);

    // MÉTODOS DE CATEGORIAS
    void obterTodasCategorias(const QString& token);
    void adicionarCategoria(const Categoria& categoria, const QString& token);
    void editarCategoria(const Categoria& categoria, const QString& token);
    void excluirCategoria(int idCategoria, const QString& token);

signals:
    void contasRecebidas(const QVector<Conta>& contas);
    void contaModificadaComSucesso();
    void categoriasRecebidas(const QVector<Categoria>& categorias);
    void categoriaModificadaComSucesso();
    void onContaError(const QString& mensagem);

private slots:
    void onObterContasReply();
    void onModificarContaReply();
    void onObterCategoriasReply();
    void onModificarCategoriaReply();

private:
    QNetworkAccessManager *m_manager;
};

#endif // CONTADAO_H