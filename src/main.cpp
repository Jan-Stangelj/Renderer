#include <renderer.hpp>
#include <shader.hpp>
#include <ebo.hpp>
#include <vbo.hpp>
#include <vao.hpp>
#include <texture.hpp>

#include <glm/glm.hpp>

#include <iostream>


int main(){
    Renderer::Window window(1920, 1080, "OpenGL", true);

    float vertices[] = {
         0.5f,  0.5f, 0.0f, 1.77f, 1.0f,  // top right
         0.5f, -0.5f, 0.0f, 1.77f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f ,  // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    }; 
    
    Renderer::VAO VAO;

    Renderer::VBO VBO(vertices, sizeof(vertices));
    Renderer::EBO EBO(indices, sizeof(indices));

    VAO.addAttribute(Renderer::vertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
    VAO.addAttribute(Renderer::vertexAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));

    Renderer::Shader shader("../src/shaders/basic.vert", "../src/shaders/basic.frag");

    Renderer::Texture texture("../assets/textures/red_brick.jpg", 0, shader, "texture1", 3);

    while (!window.shouldWindowClose()){
        window.clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        window.swapBuffers();
    }

    return 0;
}
