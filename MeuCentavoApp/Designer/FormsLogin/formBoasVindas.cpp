//
// Created by bruno on 04/07/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_formBoasVindas.h" resolved

#include "formBoasVindas.h"
#include "ui_formBoasVindas.h"
#include "formBoasVindas.h"
#include "formCadastro.h"
#include "Designer/formInicio.h"

formBoasVindas::formBoasVindas(QSqlDatabase db,QWidget *parent) :
    QWidget(parent), ui(new Ui::formBoasVindas), m_db(db) {
    ui->setupUi(this);
    m_formCadastro = nullptr;
    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->buttonCriarUsuario, &QPushButton::clicked, this, &formBoasVindas::abrirTelaCadastro);

}


formBoasVindas::~formBoasVindas() {
    delete ui;
}

void formBoasVindas::abrirTelaCadastro()
{
    if (!m_formCadastro) {
        m_formCadastro = new formCadastro(m_db, nullptr);

        // Conecta o sinal de sucesso do cadastro a um slot nesta janela
        connect(m_formCadastro, &formCadastro::cadastroConcluido,
                this, &formBoasVindas::onCadastroConcluido);
    }
    m_formCadastro->show();
}

void formBoasVindas::onCadastroConcluido()
{
    // Quando o primeiro usuário for cadastrado, esta função é chamada.
    // Ela cria e mostra a janela principal do aplicativo.
    formInicio *inicioWindow = new formInicio(m_db);
    inicioWindow->show();

    // Fecha a si mesma, completando a transição.
    this->close();
}