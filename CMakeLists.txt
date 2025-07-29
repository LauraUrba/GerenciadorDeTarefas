cmake_minimum_required(VERSION 3.31)
project(GerenciadorTarefas1)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(GerenciadorTarefas1
        main.cpp
        Process.h Process.cpp
        ProcessMonitor.h ProcessMonitor.cpp
        GUI.h GUI.cpp
)

target_link_libraries(GerenciadorTarefas1
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

set_target_properties(GerenciadorTarefas1 PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        AUTOMOC ON
        AUTORCC ON
        AUTOUIC ON
)
