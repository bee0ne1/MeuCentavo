cmake_minimum_required(VERSION 3.16)
project(MeuCentavoApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontra o pacote do Qt6 com os módulos que precisamos (Widgets e Sql)
find_package(Qt6 COMPONENTS Widgets Sql REQUIRED)

# Configurações para que o Qt funcione magicamente com o CMake
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# --- AQUI ESTÁ A ORGANIZAÇÃO CORRETA ---

# 1. Criamos uma lista apenas com os arquivos de código-fonte (.cpp)
set(PROJECT_SOURCES
        main.cpp
        DataAccess/LancamentoDAO.cpp
        DataAccess/UsuarioDAO.cpp
        Designer/formMain.cpp
        Designer/Forms/formCadastro.cpp
        Designer/Forms/formExcluirUsuario.cpp
        Designer/Forms/formUsuario.cpp
)

# 2. Criamos uma lista apenas com os arquivos de interface (.ui)
set(PROJECT_FORMS
        Designer/formMain.ui
        Designer/Forms/formCadastro.ui
        Designer/Forms/formExcluirUsuario.ui
        Designer/Forms/formUsuario.ui
)

# 3. Criamos o executável usando uma função especial do Qt
#    Ela entende essas listas e lida com tudo automaticamente
qt_add_executable(MeuCentavoApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_FORMS}
)

target_include_directories(MeuCentavoApp PRIVATE ${PROJECT_SOURCE_DIR})

# 4. Linkamos as bibliotecas do Qt ao nosso executável
target_link_libraries(MeuCentavoApp PRIVATE
        Qt6::Widgets
        Qt6::Sql
)

# Finaliza as configurações do MOC, UIC, e RCC
qt_finalize_executable(MeuCentavoApp)