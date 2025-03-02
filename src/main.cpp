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
    Renderer::Window Window(1280, 720, "Renderer", false);

    glfwSetInputMode(Window.getGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(Window.getGlfwWindow(), mouseCallback);

    Renderer::Shader shader("../src/shaders/basic.vert", "../src/shaders/basic.frag");
    shader.use();

    Renderer::Model sponza("../assets/models/sponza/Sponza.gltf");
    Renderer::Model helmet("../assets/models/helmet/DamagedHelmet.gltf");

    Renderer::PointLight light(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f), 16.0f);
    light.Bind(shader, 0);
    Renderer::PointLight light2(glm::vec3(3.0f, 2.0f, 0.0f), glm::vec3(1.0f), 16.0f);
    light2.Bind(shader, 1);
    Renderer::PointLight light3(glm::vec3(-3.0f, 2.0f, 0.0f), glm::vec3(1.0f), 16.0f);
    light3.Bind(shader, 2);

    Renderer::SpotLight light4(glm::vec3(0.0f, 4.0f, 1.0f), glm::vec3(1.0f), 16.0f, glm::vec3(0.0f, 0.0f, -1.0f), 15.0f, 60.0f);
    light4.Bind(shader, 0);


    shader.setInt("numPointLights", 3);
    shader.setInt("numSpotLights", 1);
    shader.setInt("numDirLights", 0);

    // Camera
    Renderer::Camera cam(60.0f, Window.resolution().x/Window.resolution().y, 0.15f, 100.0f);
    cam.setPosition(glm::vec3(0.0f, 3.0f, 0.0f));

    // Main loop
    while (!Window.shouldWindowClose()){
        auto start = std::chrono::high_resolution_clock::now();
        Window.clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
        shader.setVec3("skybox", glm::vec3(0.2f, 0.2f, 0.3f));

        // Camera movement calls
        cam.cameraMovement(Window, Window.deltaTime(), 1.0f);
        cam.cameraRotation(0.05f, mouseX, mouseY);
        cam.applyToShader(shader);

        shader.setVec3("camPos", cam.getPosition());

        // Object translation
        glm::mat4 trans(1.0f);
        trans = glm::scale(trans, glm::vec3(0.005f));
        shader.setMat4("model", trans);

        sponza.draw(shader);

        trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(0.3f));
        trans = glm::translate(trans, glm::vec3(0.0f, 3.0f, 0.0f));
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shader.setMat4("model", trans);
        helmet.draw(shader);
        
        Window.swapBuffers();

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Frametime: " << duration.count() / 1000.0f << "\n";
    }
    return 0;
}