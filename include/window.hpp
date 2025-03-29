#pragma once
#define RENDERER_DEBUG

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"

#include <string>

namespace Renderer{
    class Window{
    public:

        Window(unsigned int Width, unsigned int Height, const std::string& Title, bool VSync);
        ~Window();

        bool shouldWindowClose();

        void clear(const glm::vec3& Color);
        void swapBuffers();

        GLFWwindow* getGlfwWindow();

        float deltaTime() { return dTime; };
        glm::vec2 resolution() { return glm::vec2(width, height); }

    private:

        GLFWwindow* window;

        unsigned int width;
        unsigned int height;
        bool vsync;
        std::string title;

        float dTime;

    };
}
