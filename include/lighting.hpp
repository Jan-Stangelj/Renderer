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

    void setMaterial(Renderer::Shader &Shader, Renderer::Texture &Diffuse, Renderer::Texture &Specular, Renderer::Texture &AO, float Smoothnes) {
        Diffuse.Bind(0, Shader, "mat.diffuse");
        Specular.Bind(1, Shader, "mat.specular");
        AO.Bind(2, Shader, "mat.ambientOcclusion");
        Shader.setFloat("mat.smoothnes", Smoothnes);
    }

    void setMaterial(Renderer::Material Material) {
        Material.Diffuse.Bind(0, Material.Shader, "mat.diffuse");
        Material.Specular.Bind(1, Material.Shader, "mat.specular");
        Material.AO.Bind(2, Material.Shader, "mat.ambientOcclusion");
        Material.Shader.setFloat("mat.smoothnes", Material.Smoothnes);
    }

    struct Light {
        glm::vec3 Position;
        glm::vec3 Color;
        float Strength;
        float Ambient;

        Light(glm::vec3 position, glm::vec3 color, float strength, float ambient)
        : Position(position), 
          Color(color), 
          Strength(strength), 
          Ambient(ambient) {}
    };

    void setLight(Renderer::Shader &Shader, Renderer::Light &light) {
        Shader.setVec3("light.position", light.Position);
        Shader.setVec3("light.color", light.Color);
        Shader.setFloat("light.strenght", light.Strength);
        Shader.setFloat("light.ambient", light.Ambient);
    }
    
}