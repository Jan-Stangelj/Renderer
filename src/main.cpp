#include <renderer.hpp>
#include <shader.hpp>
#include <ebo.hpp>
#include <vbo.hpp>
#include <vao.hpp>
#include <texture.hpp>
#include <camera.hpp>
#include <lighting.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

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

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    
    // Mesh
    Renderer::VAO VAO;
    Renderer::VBO VBO(vertices, sizeof(vertices));
    VAO.addAttribute(Renderer::vertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
    VAO.addAttribute(Renderer::vertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
    VAO.addAttribute(Renderer::vertexAttribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));

    // Textures, materials and lights
    Renderer::Texture texture("../assets/textures/red_brick_diff_4k.jpg", 3);
    Renderer::Texture texture2("../assets/textures/red_brick_spec_1k.jpg", 1);
    Renderer::Texture texture3("../assets/textures/red_brick_ao_1k.jpg", 1);
    Renderer::setMaterial(shader, texture, texture2, texture3, 16.0f);

    Renderer::Light light(glm::vec3(1.5f, 1.5f, 1.5f), glm::vec3(1.0f), 20.0f, 0.15f);
    Renderer::setLight(shader, light);


    // Camera
    Renderer::Camera cam(60.0f, Window.resolution().x/Window.resolution().y, 0.01f, 100.0f, shader);
    cam.setPosition(glm::vec3(0.0f, 0.0f, -3.0f));

    // Main loop
    while (!Window.shouldWindowClose()){
        Window.clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        // Camera movement calls
        cam.cameraMovement(Window, Window.deltaTime(), 1.0f);
        cam.cameraRotation(0.05f, mouseX, mouseY);

        shader.setVec3("camPos", cam.getPosition());

        // Object translation
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shader.setMat4("model", trans);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        Window.swapBuffers();
    }
    return 0;
}
