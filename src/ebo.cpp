#include "ebo.hpp"

Renderer::EBO::EBO(const void* data, unsigned int size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
Renderer::EBO::~EBO() {
	glDeleteBuffers(1, &ID);
}

void Renderer::EBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void Renderer::EBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}