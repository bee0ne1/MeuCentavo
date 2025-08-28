#ifndef DIALOGADDEDITCONEXAO_H
#define DIALOGADDEDITCONEXAO_H

#include <QDialog>
#include <QUrl>

class LancamentoDAO;
class QWebEngineView; // Use forward declaration
namespace Ui { class dialogAddEditConexao; }

class dialogAddEditConexao : public QDialog
{
    Q_OBJECT

public:
    explicit dialogAddEditConexao(QWidget *parent = nullptr);
    ~dialogAddEditConexao();

    signals:
        // Sinal para avisar a tela principal que uma conexão foi feita com sucesso
        void conexaoSucedida();

private slots:
    // Recebe o token do DAO e carrega a URL da Pluggy
    void onConnectTokenRecebido(const QString& connectToken);

    // Monitora a URL do webView para detectar a conclusão do processo
    void onUrlChanged(const QUrl& url);

    void onErro(const QString& motivo);

private:
    Ui::dialogAddEditConexao *ui;
    LancamentoDAO* m_dao;
    QWebEngineView* m_webView; // Ponteiro para o nosso navegador
};

#endif // DIALOGADDEDITCONEXAO_H
