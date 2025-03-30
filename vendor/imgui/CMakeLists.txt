cmake_minimum_required(VERSION 3.16)
project("imgui")

add_library("imgui")

set(IMGUI_SOURCES
    ${PROJECT_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
   )

target_sources("imgui" PRIVATE ${IMGUI_SOURCES})
target_include_directories("imgui" PUBLIC ${PROJECT_SOURCE_DIR}/imgui)
target_include_directories("imgui" PUBLIC ${PROJECT_SOURCE_DIR}/imgui/backends)