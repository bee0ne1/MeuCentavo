#include "Designer/formInicio.h"
#include "Designer/FormsLogin/formBoasVindas.h"
#include "DataAccess/UsuarioDAO.h"
#include <QApplication>
#include <QDebug>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Não precisamos mais da conexão com o banco aqui!
    // O backend que cuida disso.

    // A lógica de qual janela abrir precisa ser assíncrona
    UsuarioDAO dao;
    QWidget *janelaParaMostrar = nullptr;

    // Usamos um truque com QEventLoop para esperar a resposta da API
    QEventLoop loop;
    QObject::connect(&dao, &UsuarioDAO::usuarioInicialRecebido, [&](const std::optional<Usuario>& usuario) {
        if (usuario) {
            qDebug() << "main: Usuários existem. Abrindo formInicio.";
            janelaParaMostrar = new formInicio();
        } else {
            qDebug() << "main: Nenhum usuário. Abrindo formBoasVindas.";
            janelaParaMostrar = new formBoasVindas();
        }
        loop.quit(); // Sai do loop de espera
    });
    QObject::connect(&dao, &UsuarioDAO::erroDeRede, [&](const QString& erro){
        qDebug() << "main: Erro de rede ao verificar usuários. Não é possível iniciar." << erro;
        // Poderia mostrar uma QMessageBox aqui
        loop.quit();
    });

    dao.obterUsuarioInicial(); // Dispara a requisição
    loop.exec(); // Pausa aqui até o sinal ser recebido

    if (janelaParaMostrar) {
        janelaParaMostrar->show();
    } else {
        return -1; // Falha ao iniciar
    }

    return app.exec();
}