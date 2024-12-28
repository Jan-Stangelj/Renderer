#pragma once

#include <glad/glad.h>
#include <shader.hpp>


namespace Renderer {
    class Texture {
    public:
        Texture(std::string file, unsigned int textureUint, Renderer::Shader &shader, std::string textureUniform, unsigned int colorChannels);
        ~Texture();

        void Bind(unsigned int textureUint, Renderer::Shader &shader, std::string textureUniform);
        void Unbind();
    private:
        GLuint ID; 
    };
}