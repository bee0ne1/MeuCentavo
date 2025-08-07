#ifndef DIALOGSIMULARPLANO_H
#define DIALOGSIMULARPLANO_H

#include <QDialog>
#include "DataAccess/LancamentoDAO.h" // Necessário para a struct LinhaCronograma e o DAO

namespace Ui {
    class dialogSimularPlano;
}

class dialogSimularPlano : public QDialog
{
    Q_OBJECT

public:
    explicit dialogSimularPlano(QWidget *parent = nullptr);
    ~dialogSimularPlano();

private slots:
    // Slot para o clique do botão "Simular Plano" (será auto-conectado)
    void on_buttonSimularPlano_clicked();

    // Slot para receber o resultado da simulação vindo do DAO
    void onPlanoRecebido(const QVector<LinhaCronograma>& cronograma, int mesesTotais);
    
    // Slot para tratar erros de rede
    void onErro(const QString& motivo);

private:
    Ui::dialogSimularPlano *ui;
    LancamentoDAO* m_dao;
};

#endif // DIALOGSIMULARPLANO_H