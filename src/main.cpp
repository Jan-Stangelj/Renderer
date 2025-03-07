#include "window.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "lighting.hpp"
#include "model.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <chrono>

float mouseX;
float mouseY;

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    mouseX = xposIn;
    mouseY = yposIn;
}

int main(){ 
    Renderer::Window Window(1280, 720, "Renderer", true);

    glfwSetInputMode(Window.getGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(Window.getGlfwWindow(), mouseCallback);

    Renderer::Shader shader("../src/shaders/basic.vert", "../src/shaders/basic.frag");
    shader.use();
    shader.setVec3("skybox", glm::vec3(0.2f, 0.2f, 0.3f));

    Renderer::Model sponza("../assets/models/sponza/Sponza.gltf");
    sponza.size = glm::vec3(0.005f);

    Renderer::Model helmet("../assets/models/helmet/DamagedHelmet.gltf");
    helmet.size = glm::vec3(0.25f);
    helmet.position = glm::vec3(0.0f, 1.0f, 0.0f);
    helmet.rotation = glm::vec3(90.0f, 0.0f, 0.0f);

    Renderer::PointLight light(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f), 64.0f);
    light.Bind(shader, 0);
    Renderer::PointLight light2(glm::vec3(3.0f, 2.0f, 0.0f), glm::vec3(1.0f), 32.0f);
    light2.Bind(shader, 1);
    Renderer::PointLight light3(glm::vec3(-3.0f, 2.0f, 0.0f), glm::vec3(1.0f), 32.0f);
    light3.Bind(shader, 2);

    Renderer::SpotLight light4(glm::vec3(0.0f, 4.0f, 1.0f), glm::vec3(1.0f), 16.0f, glm::vec3(0.0f, 0.0f, -1.0f), 15.0f, 60.0f);
    light4.Bind(shader, 0);


    shader.setInt("numPointLights", 3);
    shader.setInt("numSpotLights", 1);
    shader.setInt("numDirLights", 0);

    // Camera
    Renderer::Camera cam(60.0f, Window.resolution().x/Window.resolution().y, 0.1f, 1000.0f);
    cam.setPosition(glm::vec3(0.0f, 3.0f, 0.0f));

    shader.setFloat("exposure", 0.8f);

    // Main loop
    while (!Window.shouldWindowClose()){
        Window.clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        cam.cameraMovement(Window, Window.deltaTime(), 1.5f);
        cam.cameraRotation(0.05f, mouseX, mouseY);
        cam.applyToShader(shader);

        sponza.draw(shader);
        helmet.draw(shader);
        
        Window.swapBuffers();
    }
    return 0;
}