#pragma once

#include <texture.hpp>
#include <shader.hpp>
#include <glm/glm.hpp>

#include <string>

namespace Renderer {
    class Material {
    public:
        Material(std::string albedo, std::string AO, std::string roughness, std::string metallic);
        Material(glm::vec3 albedo, float AO, float roughness, float metallic);
        Material() = default;

        void Bind(Renderer::Shader Shader);

        void setAlbedo(glm::vec3 albedo);
        void setAO(float AO);
        void setRoughness(float roughness);
        void setMetallic(float metallic);

        void setAlbedoTexture(std::string albedo);
        void setAOTexture(std::string AO);
        void setRoughnessTexture(std::string roughness);
        void setMetallicTexture(std::string metallic);

    private:

        // error if not on heap, i dont fucking know why
        Renderer::Texture albedoTxt; 
        Renderer::Texture aoTxt; 
        Renderer::Texture roughnessTxt; 
        Renderer::Texture metallicTxt;

        glm::vec3 albedo = glm::vec3(1.0f);
        float AO = 1.0f;
        float roughness = 1.0f;
        float  metallic = 0.0f;

        bool hasAlbedo = false;
        bool hasAO = false;
        bool hasRoughness = false;
        bool hasMetallic = false;
    };
}
