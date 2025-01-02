#pragma once

#include <GLFW/glfw3.h>

#include <shader.hpp>
#include <renderer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Renderer {
    class Camera {
    public:
        Camera(float fovY, float aspectRatio, float viewDistanceMin, float viewDistanceMax, Renderer::Shader &Shader);
        ~Camera() = default;

        void setPosition(glm::vec3 Position);
        void addPositionAbsolute(glm::vec3 Position);
        void addPositionRelative(glm::vec3 Position);

        void setTarget(glm::vec3 Target);

        void cameraMovement(Renderer::Window &Window, float deltaTime, float cameraSpeed);
        void cameraRotation(float mouseSensetivity, float xpos, float ypos);

        glm::vec3 getPosition() { return position; };

    private:

        Renderer::Shader shader;

        glm::mat4 view;
        glm::mat4 projection;

        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 target;

        glm::vec3 up;
        glm::vec3 right;

        float fov;
        float aspectR;
        float VDmin;
        float VDmax;

        float mouseSens;
        float lastX = 100.0f;
        float lastY = 100.0f;
        bool firstMouse = true;
        float yaw = -90.0f;
        float pitch = 0.0f;

    };
}