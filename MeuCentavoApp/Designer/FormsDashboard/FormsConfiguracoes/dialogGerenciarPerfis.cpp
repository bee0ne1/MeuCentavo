#include "dialogGerenciarPerfis.h"
#include "ui_dialogGerenciarPerfis.h"
#include "Gerenciamento/SessionManager.h"
#include <QMessageBox>

dialogGerenciarPerfis::dialogGerenciarPerfis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogGerenciarPerfis)
{
    ui->setupUi(this);
    setWindowTitle("Gerenciar Perfis");

    m_dao = new UsuarioDAO(this);

    // Conecta os sinais do DAO aos slots deste diálogo
    connect(m_dao, &UsuarioDAO::perfisRecebidos, this, &dialogGerenciarPerfis::onPerfisRecebidos);
    connect(m_dao, &UsuarioDAO::erroDeRede, this, &dialogGerenciarPerfis::onErro);
    connect(m_dao, &UsuarioDAO::perfilAdicionadoComSucesso, this, &dialogGerenciarPerfis::onPerfilAdicionado);
    connect(m_dao, &UsuarioDAO::perfilExcluidoComSucesso, this, &dialogGerenciarPerfis::onPerfilExcluido);
    connect(ui->listWidgetPerfis, &QListWidget::itemSelectionChanged, this, &dialogGerenciarPerfis::onSelecaoAlterada);

    // Conecta o botão de fechar
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    // Inicia o carregamento dos perfis assim que a janela é criada
    carregarPerfis();
}

dialogGerenciarPerfis::~dialogGerenciarPerfis()
{
    delete ui;
}

void dialogGerenciarPerfis::carregarPerfis()
{
    QString token = SessionManager::instance().getToken();
    if (!token.isEmpty()) {
        m_dao->obterPerfis(token);
    }
}

void dialogGerenciarPerfis::onPerfisRecebidos(const QVector<Perfil>& perfis)
{
    // 1. Armazena a lista de perfis recebida como um membro da classe
    m_perfis = perfis;

    ui->listWidgetPerfis->clear();
    // 2. Usamos um loop com índice
    for (int i = 0; i < m_perfis.size(); ++i) {
        const auto& perfil = m_perfis[i];
        QString textoItem = QString("%1 (%2)").arg(perfil.nome_perfil).arg(perfil.tipo_perfil);
        QListWidgetItem* item = new QListWidgetItem(textoItem);

        // --- CORREÇÃO CRÍTICA AQUI ---
        // Em vez de guardar o objeto, guardamos o seu ÍNDICE na nossa lista m_perfis
        item->setData(Qt::UserRole, i);
        // -----------------------------

        ui->listWidgetPerfis->addItem(item);
    }
    onSelecaoAlterada();
}

void dialogGerenciarPerfis::on_buttonSalvarPerfil_clicked()
{
    if (ui->lineEditNomePerfil->text().isEmpty()) {
        QMessageBox::warning(this, "Campo Obrigatório", "O nome do perfil é obrigatório.");
        return;
    }

    ui->buttonSalvarPerfil->setEnabled(false);
    ui->buttonSalvarPerfil->setText("Salvando...");

    Perfil novoPerfil;
    novoPerfil.nome_perfil = ui->lineEditNomePerfil->text();
    novoPerfil.documento = ui->lineEditDocumento->text();
    novoPerfil.razao_social = ui->lineEditRazaoSocial->text();

    QString token = SessionManager::instance().getToken();
    m_dao->adicionarPerfil(novoPerfil, token);
}


void dialogGerenciarPerfis::onErro(const QString& motivo)
{
    ui->buttonSalvarPerfil->setEnabled(true);
    ui->buttonSalvarPerfil->setText("Salvar Novo Perfil");
    QMessageBox::critical(this, "Erro", motivo);
}

void dialogGerenciarPerfis::on_buttonExcluirPerfil_clicked()
{
    QListWidgetItem* itemSelecionado = ui->listWidgetPerfis->currentItem();
    if (!itemSelecionado) return;

    // Recupera o ÍNDICE do item
    int index = itemSelecionado->data(Qt::UserRole).toInt();
    // Pega o perfil correto da nossa lista de membros usando o índice
    const Perfil& perfilSelecionado = m_perfis[index];


    // A verificação de segurança agora está na UI, mas a do backend continua como garantia
    if (perfilSelecionado.tipo_perfil == "PF") {
        QMessageBox::warning(this, "Ação Inválida", "O perfil principal de Pessoa Física não pode ser excluído.");
        return;
    }
    QMessageBox::StandardButton resposta = QMessageBox::question(this, "Confirmar Exclusão",
        QString("Tem certeza que deseja excluir o perfil '%1'?\n\nATENÇÃO: Todos os dados associados a este perfil (contas, lançamentos, etc.) serão permanentemente perdidos.")
        .arg(perfilSelecionado.nome_perfil),
        QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        QString token = SessionManager::instance().getToken();
        m_dao->excluirPerfil(perfilSelecionado.id_perfil, token);
    }
}

void dialogGerenciarPerfis::onSelecaoAlterada()
{
    QListWidgetItem* itemSelecionado = ui->listWidgetPerfis->currentItem();

    // Se nada estiver selecionado, o botão fica desabilitado.
    if (!itemSelecionado) {
        ui->buttonExcluirPerfil->setEnabled(false);
        return;
    }

    // --- LÓGICA DE BLOQUEIO APRIMORADA ---

    // 1. Pega o ID do perfil que está ATIVO na sessão.
    int perfilAtivoId = SessionManager::instance().getPerfilId();

    // 2. Recupera o objeto Perfil completo do item da lista que foi clicado.
    int index = itemSelecionado->data(Qt::UserRole).toInt();
    if (index < 0 || index >= m_perfis.size()) { // Segurança extra
        ui->buttonExcluirPerfil->setEnabled(false);
        return;
    }
    const Perfil& perfilSelecionado = m_perfis[index];

    // 3. Define as três condições para que a exclusão seja permitida.
    bool isTipoPJ = (perfilSelecionado.tipo_perfil == "PJ");
    bool naoEhOPerfilAtivo = (perfilSelecionado.id_perfil != perfilAtivoId);

    // O botão só será habilitado se TODAS as condições forem verdadeiras.
    ui->buttonExcluirPerfil->setEnabled(isTipoPJ && naoEhOPerfilAtivo);
}

void dialogGerenciarPerfis::onPerfilAdicionado()
{
    ui->buttonSalvarPerfil->setEnabled(true);
    ui->buttonSalvarPerfil->setText("Salvar Novo Perfil");

    // Limpa os campos de texto
    ui->lineEditNomePerfil->clear();
    ui->lineEditDocumento->clear();
    ui->lineEditRazaoSocial->clear();

    // Mensagem correta para adição
    QMessageBox::information(this, "Sucesso", "Novo perfil PJ adicionado com sucesso!");

    // Recarrega a lista para mostrar o novo perfil
    carregarPerfis();
}


void dialogGerenciarPerfis::onPerfilExcluido()
{
    // Mensagem correta para exclusão
    QMessageBox::information(this, "Sucesso", "Perfil excluído com sucesso!");

    // Recarrega a lista para remover o perfil excluído
    carregarPerfis();
}

