#ifndef DIALOGGERENCIARPERFIS_H
#define DIALOGGERENCIARPERFIS_H

#include <QDialog>
#include "DataAccess/UsuarioDAO.h" // Precisa do DAO e do Perfil.h
#include "Modelo/Perfil.h"

namespace Ui {
    class dialogGerenciarPerfis;
}

class dialogGerenciarPerfis : public QDialog
{
    Q_OBJECT

public:
    explicit dialogGerenciarPerfis(QWidget *parent = nullptr);
    ~dialogGerenciarPerfis();

private slots:
    // Slots para os resultados do DAO
    void onPerfisRecebidos(const QVector<Perfil>& perfis);
    void onPerfilAdicionado(); // Slot para o sucesso da ADIÇÃO
    void onPerfilExcluido();   // NOVO slot para o sucesso da EXCLUSÃO
    void onErro(const QString& motivo);

    // Slot para o clique do botão de salvar
    void on_buttonSalvarPerfil_clicked();
    void on_buttonExcluirPerfil_clicked();
    void onSelecaoAlterada();

signals:
    void perfisModificados(); // Avisa que a lista de perfis mudou

private:
    void carregarPerfis(); // Função para iniciar a busca dos perfis

    Ui::dialogGerenciarPerfis *ui;
    UsuarioDAO* m_dao;
    QVector<Perfil> m_perfis;
};

#endif // DIALOGGERENCIARPERFIS_H