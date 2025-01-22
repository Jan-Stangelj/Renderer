#pragma once

#include <texture.hpp>
#include <shader.hpp>
#include <string>

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

    struct PointLight {

        glm::vec3 Position;
        glm::vec3 Color;
        float Strength;
        float Ambient;

        PointLight(glm::vec3 position, glm::vec3 color, float strength, float ambient)
        : Position(position), 
          Color(color), 
          Strength(strength), 
          Ambient(ambient) {}
    };

    struct DirectionLight {

        glm::vec3 Direction;
        glm::vec3 Color;
        float Intensity;
        float Ambient;

        DirectionLight(glm::vec3 direction, glm::vec3 color, float intensity, float ambient)
        : Direction(direction), 
        Color(color), 
        Intensity(intensity), 
        Ambient(ambient) {}
    };
    void setLight(Renderer::Shader &Shader, Renderer::PointLight &light, int index);
    void setLight(Renderer::Shader &Shader, Renderer::DirectionLight &light, int index);
}