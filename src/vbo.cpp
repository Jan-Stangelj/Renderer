#include "vbo.hpp"

Renderer::VBO::VBO(const void* data, unsigned int size) {
	glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
Renderer::VBO::~VBO() {
	glDeleteBuffers(1, &ID);
}

void Renderer::VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void Renderer::VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}