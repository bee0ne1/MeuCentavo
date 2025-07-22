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
        m_formCadastro = new formCadastro(this); // Pode ser modal agora
        m_formCadastro->setWindowModality(Qt::ApplicationModal);
        m_formCadastro->setAttribute(Qt::WA_DeleteOnClose);


        connect(m_formCadastro, &QObject::destroyed, this, [=](){ m_formCadastro = nullptr; });
    }
    // Em vez de show() ou open(), exec() é bom para diálogos modais simples
    m_formCadastro->exec();
}

