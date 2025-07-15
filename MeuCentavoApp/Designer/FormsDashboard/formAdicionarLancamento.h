#ifndef FORMADICIONARLANCAMENTO_H
#define FORMADICIONARLANCAMENTO_H

#include <QDialog>

// Forward declaration
namespace Ui { class formAdicionarLancamento; }

class formAdicionarLancamento : public QDialog
{
    Q_OBJECT

public:
    // O construtor agora é muito mais simples. Ele buscará o ID do usuário
    // do SessionManager quando precisar.
    explicit formAdicionarLancamento(QWidget *parent = nullptr);
    ~formAdicionarLancamento();

signals:
        // Sinal para avisar a página de lançamentos que a lista precisa ser atualizada.
    void lancamentoSalvo();

private slots:
    // Slot conectado ao clique do botão Salvar.
    void salvarLancamento();

    // Slots que reagem aos sinais de resposta do DAO.
    void onLancamentoAdicionado();
    void onErroDeRede(const QString& motivo);

private:
    Ui::formAdicionarLancamento *ui;
};

#endif // FORMADICIONARLANCAMENTO_H