#pragma once

#include "glad/glad.h"

#include <vector>

// index size type normalized stride (void*)0

namespace Renderer {

    struct vertexAttribute {
        GLuint index;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLsizei stride;
        void* pointer;

        vertexAttribute(GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, void* Pointer)
        : index(Index), size(Size), type(Type), normalized(Normalized), stride(Stride), pointer(Pointer) {}
    };

    class VAO {
    public:
        VAO();
        ~VAO();

        void addAttribute(const vertexAttribute& Attribute);

        void bind();
        void unbind();

        GLuint ID;

        unsigned int attribute_counter = 0;
    };
}