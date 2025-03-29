#pragma once

#include "GLFW/glfw3.h"

#include "shader.hpp"
#include "window.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Renderer {
    class Camera {
    public:
        Camera(float fovY, float aspectRatio, float viewDistanceMin, float viewDistanceMax);
        ~Camera() = default;

        void setPosition(const glm::vec3& Position);
        void addPositionAbsolute(const glm::vec3& Position);
        void addPositionRelative(const glm::vec3& Position);

        void setTarget(const glm::vec3& Target);

        void cameraMovement(Renderer::Window &Window, float deltaTime, float cameraSpeed);
        void cameraRotation(float mouseSensetivity);

        void applyToShader(Renderer::Shader& shader);

        glm::vec3 getPosition() { return position; };

    private:

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
        double xpos, ypos;
        bool firstMouse = true;
        bool mouseDown = false;
        float yaw = -90.0f;
        float pitch = 0.0f;

    };
}