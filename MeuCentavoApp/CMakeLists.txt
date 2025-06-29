cmake_minimum_required(VERSION 3.31.6)
project(MeuCentavoApp)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS
        ${CMAKE_SOURCE_DIR}/Designer
        ${CMAKE_SOURCE_DIR}/Designer/Forms
)


# Adicione Sql aqui
find_package(Qt6 COMPONENTS Core Gui Widgets Sql REQUIRED)

add_executable(MeuCentavoApp
        main.cpp
        Designer/formMain.ui
        Designer/Forms/formCadastro.cpp
        Designer/Forms/formCadastro.h
        Designer/Forms/formCadastro.ui
        Designer/formMain.cpp
        Designer/formMain.h
        Designer/Forms/formUsuario.cpp
        Designer/Forms/formUsuario.h
        Designer/Forms/formUsuario.ui
        Modelo/Lancamento.h
        Negocio/LancamentoDAO.cpp
        Negocio/LancamentoDAO.h
        Modelo/Usuario.h
        Negocio/UsuarioDAO.cpp
        Negocio/UsuarioDAO.h
)

target_include_directories(MeuCentavoApp PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/MeuCentavoApp_autogen/include
)

# Link com Qt::Sql também
target_link_libraries(MeuCentavoApp
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
)
