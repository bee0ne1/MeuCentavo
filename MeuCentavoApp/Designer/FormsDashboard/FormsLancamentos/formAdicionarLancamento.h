#ifndef FORMADICIONARLANCAMENTO_H
#define FORMADICIONARLANCAMENTO_H

#include <QDialog>
#include "Modelo/Lancamento.h"
#include "Modelo/Conta.h"
#include "Modelo/Categoria.h"
#include "Modelo/Meta.h"

// Forward declaration
class LancamentoDAO;
namespace Ui { class formAdicionarLancamento; }

class formAdicionarLancamento : public QDialog
{
    Q_OBJECT

public:
    explicit formAdicionarLancamento(QWidget *parent = nullptr);
    ~formAdicionarLancamento();
    void setLancamentoParaEdicao(const Lancamento& lancamento);

signals:
    void lancamentoSalvo();

private slots:
    void salvarLancamento();
    void onContasRecebidas(const QVector<Conta>& contas);
    void onCategoriasRecebidas(const QVector<Categoria>& categorias);
    void onLancamentoAdicionado();
    void onErroDeRede(const QString& motivo);
    void filtrarCategoriasPorTipo(); // Novo slot para o filtro inteligente
    void onMetasRecebidas(const QVector<Meta>& metas);


private:
    Ui::formAdicionarLancamento *ui;
    LancamentoDAO* m_dao; // DAO como membro da classe
    QVector<Categoria> m_todasCategorias; // Guardamos todas as categorias aqui
    int m_idLancamentoEdicao; // Guarda o ID do lançamento a ser editado
};

#endif // FORMADICIONARLANCAMENTO_H