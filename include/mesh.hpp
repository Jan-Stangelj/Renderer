#pragma once

#include <glm/glm.hpp>

#include <vbo.hpp>
#include <vao.hpp>
#include <ebo.hpp>
#include <material.hpp>
#include <shader.hpp>


#include <vector>

namespace Renderer {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
        glm::vec3 tangent;

        Vertex() = default;
        Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoord) : position(position), normal(normal), texCoord(texCoord) {}
    };

    class Mesh {
    public:
        Mesh(const std::vector<Vertex> vertices, 
             const std::vector<unsigned int> indices,
             Renderer::Material* mat);
        ~Mesh();

        void draw(Renderer::Shader shader);

    private:
        Renderer::VBO vbo;
        Renderer::VAO* vao = new Renderer::VAO();
        Renderer::EBO ebo;

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Renderer::Material* mat;
    };
}