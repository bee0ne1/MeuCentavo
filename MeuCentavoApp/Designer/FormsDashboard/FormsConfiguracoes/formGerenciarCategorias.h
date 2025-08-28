#ifndef FORMGERENCIARCATEGORIAS_H
#define FORMGERENCIARCATEGORIAS_H

#include <QDialog>
#include "Modelo/Categoria.h"

// Forward declarations
class ContaDAO;
class QTableWidget;
namespace Ui {
    class formGerenciarCategorias;
}

class formGerenciarCategorias : public QDialog
{
    Q_OBJECT

public:
    explicit formGerenciarCategorias(QWidget *parent = nullptr);
    ~formGerenciarCategorias();

private slots:
    // Slot que recebe a lista de categorias vinda da API
    void onCategoriasRecebidas(const QVector<Categoria>& categorias);

    // Slot que é chamado após uma modificação (add, edit, delete) ser bem-sucedida
    void onCategoriaModificada();

    void onSessaoAtualizada();

    // Slots para os botões principais da UI
    void on_buttonAddCategoria_clicked();
    void on_buttonEditCategoria_clicked();
    void on_buttonExcluirCategoria_clicked();

    // Slot para gerir o estado (ativado/desativado) dos botões
    void onSelectionChanged();

private:
    // Funções de ajuda para organizar o código
    void carregarCategorias();
    void configurarTabelas();
    void editarCategoria(const Categoria& categoria);
    void excluirCategoria(const Categoria& categoria);
    QString m_tipoPerfilAtivo;
    QTableWidget* tabelaAtual(); // Retorna um ponteiro para a tabela da aba ativa

    Ui::formGerenciarCategorias *ui;
    ContaDAO* m_dao;
};

#endif // FORMGERENCIARCATEGORIAS_H