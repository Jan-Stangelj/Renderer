#pragma once

#include "shader.hpp"
#include "texture.hpp"

#include "glad/glad.h"

#include "iostream"

namespace Renderer {
    class gBuffer {
    public:
      gBuffer(const glm::vec2& resolution);
      ~gBuffer();

      void bindFramebuffer();
      void unbindFramebuffer();

      void bindTextures(Renderer::Shader& shader);

      void renderQuad();
        
    private:
        
      GLuint ID;
      Renderer::Texture gAlbedo, gPosition, gNormal, gPBR, gEmission;
      GLuint quadVAO, quadVBO;

    };
}