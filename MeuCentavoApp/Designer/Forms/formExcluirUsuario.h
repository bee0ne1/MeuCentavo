//
// Created by bruno on 01/07/25.
//

#ifndef FORMEXCLUIRUSUARIO_H
#define FORMEXCLUIRUSUARIO_H

#include <QWidget>
#include <QSqlDatabase>
#include "Modelo/Usuario.h"

QT_BEGIN_NAMESPACE
namespace Ui { class formExcluirUsuario; }
QT_END_NAMESPACE

class formExcluirUsuario : public QWidget {
Q_OBJECT

public:
    explicit formExcluirUsuario(QSqlDatabase db, QWidget *parent = nullptr);
    ~formExcluirUsuario() override;

private:
    Ui::formExcluirUsuario *ui;
    QSqlDatabase m_db;

signals:
    // Sinal para avisar a janela mãe que esta foi fechada
    void exclusaoFechada();
    // Sinal para avisar que a lista de usuários mudou
    void listaDeUsuariosModificada();

private slots:
    void carregarUsuarios();
    void confirmarExclusaoUsuario(const Usuario& usuario);

protected:
    void closeEvent(QCloseEvent* event) override;

};



#endif //FORMEXCLUIRUSUARIO_H
