cmake_minimum_required(VERSION 3.16)
project(MeuCentavoApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Sql Charts Network REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# --- LISTAS DE FICHEIROS CORRETAMENTE ORGANIZADAS ---

# 1. Lista de Ficheiros de Código-Fonte (.cpp)
set(PROJECT_SOURCES
        main.cpp
        DataAccess/LancamentoDAO.cpp
        DataAccess/UsuarioDAO.cpp
        Designer/formInicio.cpp
        Designer/FormsLogin/formCadastro.cpp
        Designer/FormsLogin/formExcluirUsuario.cpp
        Designer/FormsLogin/formUsuario.cpp
        Designer/FormsLogin/formBoasVindas.cpp
        Designer/FormsLogin/formLoginSenha.cpp
        Composicoes/PasswordFormHelper.cpp
        Designer/FormsDashboard/formMainDashboard.cpp
        Designer/FormsDashboard/DashboardPages/pageHome.cpp
        Designer/FormsDashboard/DashboardPages/pageLancamentos.cpp
        Designer/FormsDashboard/formAdicionarLancamento.cpp
        Gerenciamento/SessionManager.cpp
        Gerenciamento/AppController.cpp
        Designer/FormsDashboard/DashboardPages/pageConfig.cpp
        Designer/FormsDashboard/formGerenciarCategorias.cpp
        Designer/FormsDashboard/formGerenciarContas.cpp
        Designer/FormsDashboard/dialogAddEditConta.cpp
)

# 2. Lista COMPLETA de Ficheiros de Cabeçalho (.h)
set(PROJECT_HEADERS
        DataAccess/LancamentoDAO.h
        DataAccess/UsuarioDAO.h
        Designer/formInicio.h
        Designer/FormsLogin/formCadastro.h
        Designer/FormsLogin/formExcluirUsuario.h
        Designer/FormsLogin/formUsuario.h
        Designer/FormsLogin/formBoasVindas.h
        Designer/FormsLogin/formLoginSenha.h
        Composicoes/PasswordFormHelper.h
        Designer/FormsDashboard/formMainDashboard.h
        Designer/FormsDashboard/DashboardPages/pageHome.h
        Designer/FormsDashboard/DashboardPages/pageLancamentos.h
        Designer/FormsDashboard/formAdicionarLancamento.h
        Gerenciamento/SessionManager.h
        Gerenciamento/AppController.h
        Modelo/Usuario.h
        Modelo/Lancamento.h
        Modelo/Conta.h
        Modelo/Categoria.h
        Designer/FormsDashboard/DashboardPages/pageConfig.h
        Designer/FormsDashboard/formGerenciarCategorias.h
        Designer/FormsDashboard/formGerenciarContas.h
        Designer/FormsDashboard/dialogAddEditConta.h
)

# 3. Lista de Ficheiros de Interface (.ui)
set(PROJECT_FORMS
        Designer/formInicio.ui
        Designer/FormsLogin/formCadastro.ui
        Designer/FormsLogin/formExcluirUsuario.ui
        Designer/FormsLogin/formUsuario.ui
        Designer/FormsLogin/formBoasVindas.ui
        Designer/FormsLogin/formLoginSenha.ui
        Designer/FormsDashboard/formMainDashboard.ui
        Designer/FormsDashboard/DashboardPages/pageHome.ui
        Designer/FormsDashboard/DashboardPages/pageLancamentos.ui
        Designer/FormsDashboard/formAdicionarLancamento.ui
        Designer/FormsDashboard/DashboardPages/pageConfig.ui
        Designer/FormsDashboard/formGerenciarCategorias.ui
        Designer/FormsDashboard/formGerenciarContas.ui
        Designer/FormsDashboard/dialogAddEditConta.ui
)

# 4. Criamos o executável, agora passando TODAS as listas de ficheiros
qt_add_executable(MeuCentavoApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_FORMS}
        recursos.qrc
)

target_include_directories(MeuCentavoApp PRIVATE ${PROJECT_SOURCE_DIR})

# 5. Linkamos as bibliotecas do Qt
target_link_libraries(MeuCentavoApp PRIVATE
        Qt6::Widgets
        Qt6::Sql
        Qt6::Charts
        Qt6::Network
)

# 6. Finaliza as configurações
qt_finalize_executable(MeuCentavoApp)