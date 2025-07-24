#ifndef PAGEMETAS_H
#define PAGEMETAS_H

#include <QWidget>
#include <QVector>
#include "Modelo/Meta.h"

// Forward declarations
QT_BEGIN_NAMESPACE
namespace Ui { class pageMetas; }
QT_END_NAMESPACE

class LancamentoDAO;

class pageMetas : public QWidget
{
    Q_OBJECT

public:
    explicit pageMetas(QWidget *parent = nullptr);
    ~pageMetas();

private slots:
    // Slot para receber a lista de metas vinda do DAO
    void onMetasRecebidas(const QVector<Meta>& metas);
    // Slot para tratar erros de rede
    void onErroDeRede(const QString& motivo);
    
    // Slots para os botões (a serem implementados depois)
    void on_buttonAdicionar_clicked();
    void on_buttonEditar_clicked();
    void on_buttonExcluir_clicked();
    void onMetaModificada();

private:
    // Funções auxiliares
    void carregarMetas();
    void popularTabela(const QVector<Meta>& metas);

    Ui::pageMetas *ui;
    LancamentoDAO* m_dao;
    QVector<Meta> m_metas; // Armazena a lista de metas atual
};

#endif // PAGEMETAS_H