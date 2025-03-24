#include "mesh.hpp"

Renderer::Mesh::Mesh(const std::vector<Vertex> vertices, 
                     const std::vector<unsigned int> indices,
                     std::shared_ptr<Renderer::Material> mat) 
                     : vertices(vertices), mat(mat), indices(indices) {
    vao->bind();
    vbo.generate(&vertices[0], vertices.size() * sizeof(Vertex));
    ebo.generate(&indices[0], indices.size() * sizeof(unsigned int));

    vao->addAttribute(Renderer::vertexAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
    vao->addAttribute(Renderer::vertexAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));
    vao->addAttribute(Renderer::vertexAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord)));
    vao->addAttribute(Renderer::vertexAttribute(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent)));

    vao->unbind();
}

void Renderer::Mesh::draw(Renderer::Shader shader) {
    shader.use();

    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, position);
    trans = glm::scale(trans, size);
    trans = glm::rotate(trans, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    shader.setMat4("model", trans);

    mat->Bind(shader);
    vao->bind();
    
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}