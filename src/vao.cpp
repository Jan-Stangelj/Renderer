#include "vao.hpp"

Renderer::VAO::VAO() {
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
}

Renderer::VAO::~VAO() {
    glDeleteVertexArrays(1, &ID);
}

void Renderer::VAO::addAttribute(const vertexAttribute &Attribute) {
    glVertexAttribPointer(Attribute.index, Attribute.size, Attribute.type, Attribute.normalized, Attribute.stride, (void*)0); // index size type normalized stride (void*)0
    glEnableVertexAttribArray(0);
}

void Renderer::VAO::bind() {
    glBindVertexArray(ID);
}

void Renderer::VAO::unbind() {
    glBindVertexArray(0);
}