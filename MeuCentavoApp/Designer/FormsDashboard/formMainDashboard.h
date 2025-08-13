#ifndef FORMMAINDASHBOARD_H
#define FORMMAINDASHBOARD_H

#include <QMainWindow>

#include "DashboardPages/pageConfig.h"
#include "DashboardPages/pageInvestimentos.h"
#include "DashboardPages/pageMetas.h"
#include "Modelo/Usuario.h"
#include "Modelo/Perfil.h"

// Forward declarations
namespace Ui { class formMainDashboard; }
class pageHome;
class pageLancamentos;
class pageRelatorios;
class formUsuario;
class pageConfig;
class pageMetas;
class pageInvestimentos;
class pageDividas;
class UsuarioDAO;

class formMainDashboard : public QMainWindow
{
    Q_OBJECT

public:
    // Construtor muito mais simples! Não precisa mais receber dados.
    explicit formMainDashboard(QWidget *parent = nullptr);
    ~formMainDashboard();

private slots:
    // Slots de Navegação
    void on_buttonHome_clicked();
    void on_buttonRelatorios_clicked();
    void on_buttonLancamentos_clicked();
    void on_buttonConfiguracoes_clicked();
    void on_buttonSwitchUsuario_clicked();
    void on_buttonMetas_clicked();
    void on_buttonInvestimentos_clicked();
    void on_buttonDividas_clicked();

    // Slots para Gestão de Perfis
    void onPerfisRecebidos(const QVector<Perfil>& perfis);
    void onPerfilAlterado(int index);
    void onNovoTokenRecebido(const QString& novoToken, const Usuario& usuario);
    void onListaDePerfisModificada();


private:
    void setupPaginas();
    void carregarPerfisDoUsuario();
    void recarregarTodasAsPaginas();

    pageDividas *m_pageDividas;

    Ui::formMainDashboard *ui;
    // Não precisamos mais de m_db ou m_usuarioAtual aqui!

    // Guardamos ponteiros para as páginas para poder interagir com elas se necessário
    pageHome* m_pageHome;
    pageLancamentos* m_pageLancamentos;
    pageRelatorios* m_pageRelatorios;
    formUsuario* m_formUsuario;
    pageConfig* m_pageConfig;
    pageMetas* m_pageMetas;
    pageInvestimentos *m_pageInvestimentos;
    UsuarioDAO* m_usuarioDAO;
};

#endif // FORMMAINDASHBOARD_H