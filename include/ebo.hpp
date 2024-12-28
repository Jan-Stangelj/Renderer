#pragma once

#include <glad/glad.h>

namespace Renderer {
    class EBO {
    public:
        EBO(const void* data, unsigned int size);
        ~EBO();

        void bind();
        void unbind();
    private:

        GLuint ID;
    };
}