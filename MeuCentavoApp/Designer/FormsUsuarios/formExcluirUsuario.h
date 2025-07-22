#ifndef FORMEXCLUIRUSUARIO_H
#define FORMEXCLUIRUSUARIO_H

#include <QWidget>
#include "Modelo/Usuario.h"
#include <QVector>

namespace Ui { class formExcluirUsuario; }
class UsuarioDAO; // Forward declaration

class formExcluirUsuario : public QWidget
{
    Q_OBJECT

public:
    // O construtor agora pode receber o token de autenticação
    explicit formExcluirUsuario(const QString& token, QWidget *parent = nullptr);
    ~formExcluirUsuario();

signals:
    void exclusaoFechada();
    void listaDeUsuariosModificada();

private slots:
    void confirmarExclusaoUsuario(const Usuario& usuario);

    // Slots para receber as respostas do DAO
    void onUsuariosRecebidos(const QVector<Usuario>& usuarios);
    void onRemocaoSucesso();
    void onErro(const QString& motivo);

private:
    void carregarUsuarios(); // Agora é uma função privada que inicia a requisição

    Ui::formExcluirUsuario *ui;
    QString m_token; // Guarda o token para usar nas requisições
    UsuarioDAO* m_dao;

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // FORMEXCLUIRUSUARIO_H