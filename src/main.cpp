#include <renderer.hpp>
#include <shader.hpp>
#include <camera.hpp>
#include <lighting.hpp>
#include <model.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <chrono>

float mouseX;
float mouseY;

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    mouseX = xposIn;
    mouseY = yposIn;
}

int main(){ 
    Renderer::Window Window(1920, 1080, "OpenGL", false);

    glfwSetInputMode(Window.getGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(Window.getGlfwWindow(), mouseCallback);

    Renderer::Shader shader("../src/shaders/basic.vert", "../src/shaders/basic.frag");
    shader.use();

    std::vector<Renderer::Vertex> cube = {
        // positions          // normals           // texture coords
        Renderer::Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 0.0f)),
        Renderer::Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 0.0f)),
        Renderer::Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 1.0f)),
        Renderer::Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 1.0f))
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3
    };

    Renderer::Model sponza("../assets/models/sponza/Sponza.gltf");
    Renderer::Model helmet("../assets/models/helmet/DamagedHelmet.gltf");

    Renderer::PointLight light(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f), 4.0f);
    light.Bind(shader, 0);
    Renderer::PointLight light2(glm::vec3(3.0f, 2.0f, 0.0f), glm::vec3(1.0f), 4.0f);
    light2.Bind(shader, 1);
    Renderer::PointLight light3(glm::vec3(-3.0f, 2.0f, 0.0f), glm::vec3(1.0f), 4.0f);
    light3.Bind(shader, 2);


    shader.setInt("numPointLights", 3);
    shader.setInt("numDirLights", 0);

    // Camera
    Renderer::Camera cam(60.0f, Window.resolution().x/Window.resolution().y, 0.01f, 100.0f);
    cam.setPosition(glm::vec3(0.0f, 0.0f, -3.0f));

    // Main loop
    while (!Window.shouldWindowClose()){
        auto start = std::chrono::high_resolution_clock::now();
        Window.clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

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

        trans = glm::translate(trans, glm::vec3(8.0f, 0.0f, 0.0f));
        shader.setMat4("model", trans);
        helmet.draw(shader);

        trans = glm::translate(trans, glm::vec3(-16.0f, 0.0f, 0.0f));
        shader.setMat4("model", trans);
        helmet.draw(shader);
        
        Window.swapBuffers();

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Frametime: " << duration.count() / 1000.0f << " FPS: " << 1000000.0f / duration.count() << "\n";
    }
    return 0;
}

// TODO:
// - zorganiziraj
// - pravilni normal mapi
// - depth mapi
// - self shadowi za depth mappe
