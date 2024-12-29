#include "renderer.hpp"

#include <iostream>

Renderer::Window::Window(unsigned int Width, unsigned int Height, std::string Title, bool VSync){
    // window settings
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // Create window and OpenGL context
    window = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    if (VSync == false)
        glfwSwapInterval(VSync);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD\n";
        return;
    }

    glEnable(GL_DEPTH_TEST);

    width = Width;
    height = Height;
    title = Title;
    vsync = VSync;
}
Renderer::Window::~Window(){
    glfwTerminate();
}

bool Renderer::Window::shouldWindowClose(){
    return glfwWindowShouldClose(window);
}

void Renderer::Window::clear(glm::vec4 Color){
    glfwSetTime(0);
    glClearColor(Color.r, Color.g, Color.b, Color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::Window::swapBuffers(){
    glfwPollEvents();
    glfwSwapBuffers(window);
    dTime = glfwGetTime();
}

GLFWwindow* Renderer::Window::getGlfwWindow(){
    return window;
}