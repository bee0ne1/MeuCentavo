//
// Created by bruno on 11/07/25.
//

#ifndef FORMADICIONARLANCAMENTOS_H
#define FORMADICIONARLANCAMENTOS_H

#include <QDialog>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class formAdicionarLancamento; }
QT_END_NAMESPACE

class formAdicionarLancamento : public QDialog {
Q_OBJECT

public:
    explicit formAdicionarLancamento(int usuarioId, QSqlDatabase db,QWidget *parent = nullptr);
    ~formAdicionarLancamento() override;

signals:
    void lancamentoSalvo();
private slots:
    void on_buttonSalvar_clicked();


private:
    Ui::formAdicionarLancamento *ui;
    QSqlDatabase m_db;
    int m_usuarioId;

};


#endif //FORMADICIONARLANCAMENTOS_H
