#pragma once

#include <texture.hpp>
#include <shader.hpp>

namespace Renderer {
    struct Material {
    Renderer::Shader Shader;
    Renderer::Texture Diffuse;
    Renderer::Texture Specular;
    Renderer::Texture AO;
    float Smoothnes;

    Material(Renderer::Shader &shader, Renderer::Texture &diffuse, Renderer::Texture &specular, Renderer::Texture &ao, float smoothness)
    : Shader(shader), 
        Diffuse(diffuse), 
        Specular(specular), 
        AO(ao), 
        Smoothnes(smoothness) {}
    };
    void setMaterial(Renderer::Material &Material);
}