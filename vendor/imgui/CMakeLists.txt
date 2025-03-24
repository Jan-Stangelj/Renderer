cmake_minimum_required(VERSION 3.16)
project(imgui)

add_library(imgui)

set(IMGUI_SOURCES
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp)

target_sources(imgui PRIVATE ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC imgui)
target_include_directories(imgui PUBLIC imgui/backends)