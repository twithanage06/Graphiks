cmake_minimum_required(VERSION 3.16)

project(Graphiks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Calculator engine: no Qt dependencies
add_library(graphiks_engine STATIC
    Engine/src/tokeniser.cpp
    Engine/src/parser.cpp
    Engine/src/evaluator.cpp
)

target_include_directories(graphiks_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine/include
)

# Desktop graphical interface
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(graphiks
    Display/main.cpp
)

target_link_libraries(graphiks PRIVATE
    graphiks_engine
    Qt6::Widgets
)
