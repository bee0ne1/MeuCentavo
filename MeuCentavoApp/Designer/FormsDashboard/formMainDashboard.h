#ifndef FORMMAINDASHBOARD_H
#define FORMMAINDASHBOARD_H

#include <QMainWindow>

#include "DashboardPages/pageConfig.h"
#include "Modelo/Usuario.h"

// Forward declarations
namespace Ui { class formMainDashboard; }
class pageHome;
class pageLancamentos;
class pageRelatorios;
class formUsuario;
class pageConfig;

class formMainDashboard : public QMainWindow
{
    Q_OBJECT

public:
    // Construtor muito mais simples! Não precisa mais receber dados.
    explicit formMainDashboard(QWidget *parent = nullptr);
    ~formMainDashboard();

private slots:
    void on_buttonHome_clicked();
    void on_buttonRelatorios_clicked();
    void on_buttonLancamentos_clicked();
    void on_buttonConfiguracoes_clicked();
    void on_buttonSwitchUsuario_clicked();

private:
    void setupPaginas();

    Ui::formMainDashboard *ui;
    // Não precisamos mais de m_db ou m_usuarioAtual aqui!

    // Guardamos ponteiros para as páginas para poder interagir com elas se necessário
    pageHome* m_pageHome;
    pageLancamentos* m_pageLancamentos;
    pageRelatorios* m_pageRelatorios;
    formUsuario* m_formUsuario;
    pageConfig* m_pageConfig;
};

#endif // FORMMAINDASHBOARD_H