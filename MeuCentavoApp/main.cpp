#include <QApplication>
#include "Gerenciamento/AppController.h"
#include "Modelo/Usuario.h" // Para registrar o metatype
#include "DataAccess/LancamentoDAO.h"
#include "Modelo/Perfil.h"
#include <optional>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("MeuCentavoApp");
    app.setApplicationName("MeuCentavo");

    // Registra os tipos customizados para o sistema de Sinais e Slots
    qRegisterMetaType<Usuario>();
    qRegisterMetaType<std::optional<Usuario>>();
    qRegisterMetaType<QVector<HistoricoPatrimonio>>();
    qRegisterMetaType<QVector<PontoTendencia>>();
    qRegisterMetaType<QVector<LinhaCronograma>>();
    qRegisterMetaType<Perfil>();

    // Cria o controlador e inicia a aplicação
    AppController controller;
    controller.iniciarAplicacao();

    // Inicia o loop de eventos principal da aplicação
    return app.exec();
}