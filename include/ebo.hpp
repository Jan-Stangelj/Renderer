#pragma once

#include <glad/glad.h>

namespace Renderer {
    class EBO {
    public:
        EBO(const void* data, unsigned int size);
        EBO() = default;
        ~EBO();

        void generate(const void* data, unsigned int size);

        void bind();
        void unbind();
    private:

        GLuint ID;
    };
}