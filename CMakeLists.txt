cmake_minimum_required(VERSION 3.10)
project(P3)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

#source files
set(SOURCES
        main.cpp
        UI.cpp
        Graph.cpp
        Film.cpp
)

#Qt directories
include_directories(${Qt6Widgets_INCLUDE_DIRS})

add_executable(Project3 ${SOURCES})

#Qt6 libraries
target_link_libraries(Project3 Qt6::Widgets)



