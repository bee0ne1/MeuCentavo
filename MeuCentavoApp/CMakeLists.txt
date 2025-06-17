cmake_minimum_required(VERSION 3.31.6)
project(MeuCentavoApp)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/Designer)

# Adicione Sql aqui
find_package(Qt6 COMPONENTS Core Gui Widgets Sql REQUIRED)

add_executable(MeuCentavoApp
        main.cpp
        Designer/interfaceMeuCentavo.ui
)

# Link com Qt::Sql também
target_link_libraries(MeuCentavoApp
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
)
