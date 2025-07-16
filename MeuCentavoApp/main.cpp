#include <QApplication>
#include "Gerenciamento/AppController.h"
#include "Modelo/Usuario.h" // Para registrar o metatype
#include <optional>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Registra os tipos customizados para o sistema de Sinais e Slots
    qRegisterMetaType<Usuario>();
    qRegisterMetaType<std::optional<Usuario>>();

    // Cria o controlador e inicia a aplicação
    AppController controller;
    controller.iniciarAplicacao();

    // Inicia o loop de eventos principal da aplicação
    return app.exec();
}