#include "camera.hpp"

Renderer::Camera::Camera(float fovY, float aspectRatio, float viewDistanceMin, float viewDistanceMax, Renderer::Shader &Shader) 
    : fov(fovY), aspectR(aspectRatio), VDmin(viewDistanceMin), VDmax(viewDistanceMax), shader(Shader) {

    view = glm::translate(glm::mat4(1.0f), position);
    projection = glm::perspective(glm::radians(fovY), aspectRatio, viewDistanceMin, viewDistanceMax);

    Shader.setMat4("view", view);
    Shader.setMat4("projection", projection);
}

void Renderer::Camera::setPosition(glm::vec3 Position) {
    position = Position;
    
    view = glm::translate(glm::mat4(1.0f), position);
    shader.setMat4("view", view);
}
void Renderer::Camera::addPositionAbsolute(glm::vec3 Position) {
    position += Position;

    view = glm::translate(view, Position);
    shader.setMat4("view", view);
}
void Renderer::Camera::addPositionRelative(glm::vec3 Position) {
    position += (right * Position.x) + (up * Position.y) + (direction * Position.z);

    view = glm::translate(view, Position);
    shader.setMat4("view", view);
}

void Renderer::Camera::setTarget(glm::vec3 Target) {
    target = Target;
    direction = glm::normalize(target - position);

    right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
    up = glm::cross(direction, right);
    view = glm::lookAt(position, target, up);
    shader.setMat4("view", view);
}

void Renderer::Camera::cameraMovement(Renderer::Window &Window, float deltaTime, float cameraSpeed) {
    if (glfwGetKey(Window.getGlfwWindow(), GLFW_KEY_W) == GLFW_PRESS)
        addPositionRelative(glm::vec3(0.0f, 0.0f, 1.0f) * deltaTime * cameraSpeed);
    if (glfwGetKey(Window.getGlfwWindow(), GLFW_KEY_S) == GLFW_PRESS)
        addPositionRelative(glm::vec3(0.0f, 0.0f, -1.0f) * deltaTime * cameraSpeed);
    if (glfwGetKey(Window.getGlfwWindow(), GLFW_KEY_A) == GLFW_PRESS)
        addPositionRelative(glm::vec3(1.0f, 0.0f, 0.0f) * deltaTime * cameraSpeed);
    if (glfwGetKey(Window.getGlfwWindow(), GLFW_KEY_D) == GLFW_PRESS)
        addPositionRelative(glm::vec3(-1.0f, 0.0f, 0.0f) * deltaTime * cameraSpeed);
    if (glfwGetKey(Window.getGlfwWindow(), GLFW_KEY_E) == GLFW_PRESS)
        addPositionRelative(glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * cameraSpeed);
    if (glfwGetKey(Window.getGlfwWindow(), GLFW_KEY_Q) == GLFW_PRESS)
        addPositionRelative(glm::vec3(0.0f, -1.0f, 0.0f) * deltaTime * cameraSpeed);
    if (glfwGetKey(Window.getGlfwWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(Window.getGlfwWindow(), true);
}

void Renderer::Camera::cameraRotation(float mouseSensetivity, float xpos, float ypos) {
    mouseSens = mouseSensetivity;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= mouseSens;
    yoffset *= mouseSens;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    setTarget(position + front);
}