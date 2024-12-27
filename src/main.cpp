#include <renderer.hpp>
#include <shader.hpp>
#include <ebo.hpp>
#include <vbo.hpp>
#include <vao.hpp>

#include <glm/glm.hpp>


int main(){
    Renderer::Window window(1280, 720, "OpenGL", true);

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    }; 
    
    Renderer::VAO VAO;

    Renderer::VBO VBO(vertices, sizeof(vertices));
    Renderer::EBO EBO(indices, sizeof(indices));

    VAO.addAttribute(Renderer::vertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float)));

    Renderer::Shader shader("basic.vert", "basic.frag");

    while (!window.shouldWindowClose()){
        window.clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        window.swapBuffers();
    }

    return 0;
}
