#include <renderer.hpp>
#include <shader.hpp>
#include <ebo.hpp>
#include <vbo.hpp>
#include <vao.hpp>
#include <texture.hpp>
#include <camera.hpp>
#include <lighting.hpp>
#include <material.hpp>

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

    std::vector<float> cube = {
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
    Renderer::VBO VBO(&cube[0], sizeof(float)*cube.size());
    VAO.addAttribute(Renderer::vertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
    VAO.addAttribute(Renderer::vertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
    VAO.addAttribute(Renderer::vertexAttribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));

    // Textures, materials and lights
    Renderer::Texture albedo("../assets/textures/coast_sand_rocks_02_diff_4k.jpg", 16, 3, false);
    Renderer::Texture arm("../assets/textures/coast_sand_rocks_02_arm_4k.jpg", 16, 3, true);
    Renderer::Texture normal("../assets/textures/coast_sand_rocks_02_nor_gl_4k.jpg", 16, 3, true);
    Renderer::Texture depth("../assets/textures/coast_sand_rocks_02_disp_4k.png", 16, 1, true);
    Renderer::Material mat(albedo, arm, normal, depth);
    mat.Bind(shader);

    Renderer::PointLight light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.85f, 0.85f), 10.0f);
    light.Bind(shader, 0);

    Renderer::DirectionLight dirlight(-glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f), 5.0f);
    dirlight.Bind(shader, 0);

    shader.setInt("numPointLights", 1);
    shader.setInt("numDirLights", 1);


    // Camera
    Renderer::Camera cam(60.0f, Window.resolution().x/Window.resolution().y, 0.01f, 100.0f);
    cam.setPosition(glm::vec3(0.0f, 0.0f, -3.0f));

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
        trans = glm::scale(trans, glm::vec3(5.0f, 0.5f, 5.0f));
        shader.use();
        shader.setMat4("model", trans);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        Window.swapBuffers();
    }
    return 0;
}

// TODO:
// - zorganiziraj
// - pravilni normal mapi
// - depth mapi
// - self shadowi za depth mappe
