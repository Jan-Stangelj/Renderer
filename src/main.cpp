#include <renderer.hpp>
#include <shader.hpp>
#include <ebo.hpp>
#include <vbo.hpp>
#include <vao.hpp>
#include <texture.hpp>
#include <camera.hpp>
#include <lighting.hpp>
#include <material.hpp>
#include <mesh.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

float mouseX;
float mouseY;

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    mouseX = xposIn;
    mouseY = yposIn;
}

int main(){ 
    Renderer::Window Window(1920, 1200, "OpenGL", true);

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

    // Textures, materials and lights
    Renderer::Material mat;
    mat.setAlbedoTexture("../assets/textures/red_brick_diff_4k.jpg");
    mat.setAOTexture("../assets/textures/red_brick_ao_4k.jpg");
    mat.setRoughnessTexture("../assets/textures/red_brick_rough_4k.jpg");
    mat.setMetallic(0.0f);
    mat.Bind(shader);

    Renderer::Mesh test(cube, indices, &mat);

    Renderer::PointLight light(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f), 0.5f);
    light.Bind(shader, 0);
    Renderer::DirectionLight dirlight(-glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.2f);
    dirlight.Bind(shader, 0);

    shader.setInt("numPointLights", 1);
    shader.setInt("numDirLights", 1);

    // Camera
    Renderer::Camera cam(60.0f, Window.resolution().x/Window.resolution().y, 0.01f, 100.0f);
    cam.setPosition(glm::vec3(0.0f, 0.0f, -3.0f));

    std::cout << sizeof(test) + sizeof(mat);

    // Main loop
    while (!Window.shouldWindowClose()){
        Window.clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        // Camera movement calls
        cam.cameraMovement(Window, Window.deltaTime(), 1.0f);
        cam.cameraRotation(0.05f, mouseX, mouseY);
        cam.applyToShader(shader);

        shader.setVec3("camPos", cam.getPosition());

        // Object translation
        glm::mat4 trans(1.0f);
        trans = glm::scale(trans, glm::vec3(3.0f));
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shader.setMat4("model", trans);

        test.draw(shader);

        Window.swapBuffers();
    }
    return 0;
}

// TODO:
// - zorganiziraj
// - pravilni normal mapi
// - depth mapi
// - self shadowi za depth mappe
