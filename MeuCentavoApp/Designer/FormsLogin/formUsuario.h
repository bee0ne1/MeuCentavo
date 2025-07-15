#ifndef FORMUSUARIO_H
#define FORMUSUARIO_H

#include <QWidget>
#include <QVector>
#include "Modelo/Usuario.h"

// Forward declarations
class formCadastro;
class formExcluirUsuario;
class UsuarioDAO;
namespace Ui { class formUsuario; }

class formUsuario : public QWidget
{
    Q_OBJECT

public:
    // O construtor agora recebe o token para poder fazer requisições autenticadas
    explicit formUsuario(const QString& token, QWidget *parent = nullptr);
    ~formUsuario();

    signals:
        // Sinal para avisar qual usuário foi escolhido na lista
        void usuarioSelecionado(const Usuario& usuario);
    // Sinal para avisar que a janela foi fechada sem nenhuma escolha
    void fechado();

private slots:
    // Slots para os botões da UI
    void abrirTelaCadastro();
    void abrirTelaExcluir();

    // Slot para receber a lista de usuários vinda da API
    void onUsuariosRecebidos(const QVector<Usuario>& usuarios);
    // Slot para tratar erros de rede
    void onErroDeRede(const QString& motivo);

private:
    void carregarListaDeUsuarios(); // Inicia a requisição para buscar os usuários

    Ui::formUsuario *ui;
    QString m_token;
    UsuarioDAO* m_dao;

    // Ponteiros para as janelas filhas
    formCadastro* m_formCadastro;
    formExcluirUsuario* m_formExcluirUsuario;

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // FORMUSUARIO_H