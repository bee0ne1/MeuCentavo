#include "formBoasVindas.h"
#include "ui_formBoasVindas.h"
#include "formCadastro.h"
#include "Designer/formInicio.h" // Inclui a tela de início que será aberta

formBoasVindas::formBoasVindas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::formBoasVindas)
{
    ui->setupUi(this);
    m_formCadastro = nullptr;
    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->buttonCriarUsuario, &QPushButton::clicked, this, &formBoasVindas::abrirTelaCadastro);
}

formBoasVindas::~formBoasVindas()
{
    delete ui;
}

void formBoasVindas::abrirTelaCadastro()
{
    if (!m_formCadastro) {
        // Agora, criamos o formCadastro sem passar o banco de dados.
        // Passamos 'this' como pai para que a janela de cadastro seja
        // modal em relação à de boas-vindas.
        m_formCadastro = new formCadastro(this);
        m_formCadastro->setAttribute(Qt::WA_DeleteOnClose);

        // A conexão para saber quando o cadastro foi concluído continua essencial.
        connect(m_formCadastro, &formCadastro::cadastroConcluido,
                this, &formBoasVindas::onCadastroConcluido);
    }
    // Usamos open() para diálogos não-modais, ou exec() se quisermos bloquear.
    // Como queremos que o usuário possa interagir apenas com o cadastro,
    // podemos fazer dele um diálogo modal.
    m_formCadastro->open();
}

void formBoasVindas::onCadastroConcluido()
{
    // O formCadastro nos avisou que o primeiro usuário foi criado.
    // Agora, criamos a formInicio (que também não precisa mais do banco).
    formInicio *inicioWindow = new formInicio();
    inicioWindow->show();

    // Fecha a si mesma, completando a transição para o fluxo normal do app.
    this->close();
}