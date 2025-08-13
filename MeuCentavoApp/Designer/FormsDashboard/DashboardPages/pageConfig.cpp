//
// Created by bruno on 21/07/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_pageConfig.h" resolved

#include "pageConfig.h"
#include "ui_pageConfig.h"
#include "Designer/FormsDashboard/FormsConfiguracoes/formGerenciarCategorias.h"
#include "Designer/FormsDashboard/FormsConfiguracoes/formGerenciarContas.h"
#include "Designer/FormsDashboard/FormsConfiguracoes/dialogGerenciarPerfis.h"

pageConfig::pageConfig(QWidget *parent) :
    QWidget(parent), ui(new Ui::pageConfig) {
    ui->setupUi(this);
}

pageConfig::~pageConfig() {
    delete ui;
}

void pageConfig::on_buttonCategorias_clicked()
{
    // 1. Cria uma nova instância da janela de gestão de categorias.
    //    Passamos 'this' como pai para que ela fique associada a esta janela.
    formGerenciarCategorias *formCat = new formGerenciarCategorias(this);

    // 2. (Opcional, mas recomendado) Define que a janela será apagada da memória automaticamente quando for fechada.
    formCat->setAttribute(Qt::WA_DeleteOnClose);

    // 3. Abre a janela de forma MODAL.
    //    'exec()' mostra a janela e bloqueia a interação com as janelas de trás
    //    até que esta seja fechada.
    formCat->exec();
}

void pageConfig::on_buttonContas_clicked()
{
    formGerenciarContas *formContas = new formGerenciarContas(this);
    formContas->setAttribute(Qt::WA_DeleteOnClose);
    formContas->exec();
}

void pageConfig::on_buttonPerfil_clicked()
{
    // 1. Cria e abre o diálogo de forma modal (bloqueia a janela de trás).
    // O código aqui vai PAUSAR até que o diálogo seja fechado.
    dialogGerenciarPerfis dialogo(this);
    dialogo.exec();

    // 2. DEPOIS que o diálogo é fechado, nós emitimos o sinal.
    // Isso garante que qualquer mudança na sessão já terá sido comandada
    // antes de tentarmos atualizar a UI principal.
    emit listaDePerfisAtualizada();
}
