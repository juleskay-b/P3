cmake_minimum_required(VERSION 3.10)
project(Project3)

set(CMAKE_CXX_STANDARD 17)

# OpenGL (macOS has this built-in)
find_package(OpenGL REQUIRED)

# Add GLFW manually since CMake can't find it automatically
include_directories(
        ${CMAKE_SOURCE_DIR}
        external/imgui
        external/imgui/backends
        /opt/homebrew/Cellar/glfw/3.4/include
)

link_directories(/opt/homebrew/Cellar/glfw/3.4/lib)

set(SOURCES
        main.cpp
        UI.cpp
        Graph.cpp
        Film.cpp

        # ImGui Core
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_tables.cpp

        # ImGui Backends
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
)

add_executable(Project3 ${SOURCES})

if(APPLE)
    target_link_libraries(Project3
            glfw
            ${OPENGL_gl_LIBRARY}
            "-framework Cocoa"
            "-framework OpenGL"
            "-framework IOKit"
            "-framework CoreVideo"
    )
elseif(WIN32)
    target_link_libraries(Project3
            glfw
            ${OPENGL_gl_LIBRARY}
    )
endif()


