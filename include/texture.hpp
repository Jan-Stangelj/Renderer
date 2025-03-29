#pragma once

#include "glad/glad.h"
#include "shader.hpp"

#include <iostream>
#include <unordered_map>


namespace Renderer {
    class Texture {
    public:
        Texture(const std::string& file, bool linearColorSpace);
        Texture() = default;
        ~Texture();

        void generate(const std::string& file, bool linearColorSpace);
        void generateForFBO(unsigned int width, unsigned int height, GLint internalFormat, GLenum format);

        void Bind(unsigned int textureUint, Renderer::Shader& shader, const std::string& textureUniform);
        void Unbind();

        GLuint ID; 
    };
}