cmake_minimum_required(VERSION 4.0.2)
project(Qt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Qt main.cpp)
target_link_libraries(Qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

