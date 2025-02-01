#pragma once

#include <texture.hpp>
#include <shader.hpp>

namespace Renderer {
    class Material {
    public:
        Material(Renderer::Texture &diffuse, Renderer::Texture &arm)
        : Diffuse(diffuse), 
          Arm(arm) {}

        void Bind(Renderer::Shader &Shader);
    private:
        Renderer::Texture Diffuse;
        Renderer::Texture Arm;
    };
}