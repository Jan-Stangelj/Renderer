#include "mesh.hpp"

Renderer::Mesh::Mesh(const std::vector<Vertex> vertices, 
                     const std::vector<unsigned int> indices,
                     Renderer::Material* mat) 
                     : vertices(vertices), mat(mat), indices(indices) {
    vao.bind();
    vbo.generate(&vertices[0], vertices.size() * sizeof(Vertex));
    ebo.generate(&indices[0], indices.size() * sizeof(unsigned int));

    vao.addAttribute(Renderer::vertexAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
    vao.addAttribute(Renderer::vertexAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));
    vao.addAttribute(Renderer::vertexAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord)));

    vao.unbind();
}

void Renderer::Mesh::draw(Renderer::Shader shader) {
    shader.use();
    mat->Bind(shader);
    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}