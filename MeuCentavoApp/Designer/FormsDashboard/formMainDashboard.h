#ifndef FORMMAINDASHBOARD_H
#define FORMMAINDASHBOARD_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "Modelo/Usuario.h"

// Forward declaration da classe de UI gerada automaticamente.
// Isso evita a necessidade de incluir o "ui_...h" no cabeçalho.
QT_BEGIN_NAMESPACE
namespace Ui { class formMainDashboard; }
QT_END_NAMESPACE

class formMainDashboard : public QMainWindow
{
    Q_OBJECT

public:
    // Construtor que recebe o usuário logado e a conexão com o banco.
    explicit formMainDashboard(const Usuario& usuario, QSqlDatabase db, QWidget *parent = nullptr);
    // Destrutor para limpar a memória.
    ~formMainDashboard();

private slots:
    // Slots que serão conectados automaticamente aos botões do menu,
    // desde que os botões no Qt Designer tenham os objectName corretos
    // (ex: buttonHome, buttonRelatorios, etc.).
    void on_buttonHome_clicked();
    void on_buttonRelatorios_clicked();
    void on_buttonLancamentos_clicked();
    void on_buttonConfiguracoes_clicked();

private:
    // Ponteiro para a classe de interface gerada pelo Qt Designer.
    Ui::formMainDashboard *ui;

    // Variáveis membro para guardar informações essenciais.
    QSqlDatabase m_db;
    Usuario m_usuarioAtual;

    // Uma função privada para manter o construtor limpo.
    void setupPaginas();
};

#endif // FORMMAINDASHBOARD_H