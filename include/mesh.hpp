#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "vbo.hpp"
#include "vao.hpp"
#include "ebo.hpp"
#include "material.hpp"
#include "shader.hpp"


#include <vector>
#include <memory>

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
             std::shared_ptr<Renderer::Material> mat);
        ~Mesh() = default;

        void draw(Renderer::Shader shader);

        glm::vec3 size = glm::vec3(1.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 position = glm::vec3(0.0f);

    private:
        Renderer::VBO vbo;
        std::shared_ptr<Renderer::VAO> vao = std::make_shared<Renderer::VAO>();
        Renderer::EBO ebo;

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::shared_ptr<Renderer::Material> mat;
    };
}