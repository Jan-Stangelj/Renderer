cmake_minimum_required(VERSION 3.16)

project(Renderer LANGUAGES CXX C)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/assimp)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE VENDORSOURCES CONFIGURE_DEPENDS "vendor/bin/*.cpp")
add_executable("${CMAKE_PROJECT_NAME}" ${SOURCES} ${VENDORSOURCES})

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1) 

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC include)
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE vendor/include/imgui)
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE vendor/include)

target_link_libraries("${CMAKE_PROJECT_NAME}" glad glfw glm assimp)



