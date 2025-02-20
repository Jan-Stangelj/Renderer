#pragma once

#include <glad/glad.h>

namespace Renderer {
    class VBO {
    public:
        VBO(const void* data, unsigned int size);
        VBO() = default;
        ~VBO();

        void generate(const void* data, unsigned int size);

        void bind();
        void unbind();
    private:

        GLuint ID;
    };
}