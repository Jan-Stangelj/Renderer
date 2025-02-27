#pragma once

#include <glad/glad.h>
#include <shader.hpp>


namespace Renderer {
    class Texture {
    public:
        Texture(std::string file, bool linearColorSpace);
        Texture() = default;
        ~Texture();

        void generate(std::string file, bool linearColorSpace);

        void Bind(unsigned int textureUint, Renderer::Shader &shader, std::string textureUniform);
        void Unbind();
    private:
        GLuint ID; 
    };
}