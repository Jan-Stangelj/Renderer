#pragma once

#include <texture.hpp>
#include <shader.hpp>
#include <glm/glm.hpp>

#include <string>

namespace Renderer {
    class Material {
    public:
        Material(std::string albedo, std::string AO, std::string metallicRoughness);
        Material(glm::vec3 albedo, float AO, glm::vec3 metallicRoughness);
        Material() = default;

        void Bind(Renderer::Shader Shader);

        void setAlbedo(glm::vec3 albedo);
        void setAO(float AO);
        void setMetallicRoughness(glm::vec3 metallicRoughness);

        void setAlbedoTexture(std::string albedo);
        void setAOTexture(std::string AO);
        void setMetallicRoughnessTexture(std::string metallicRoughness);
        void setNormalTexture(std::string normal);
        void setEmissionTexture(std::string emission);

    private:

        Renderer::Texture albedoTxt; 
        Renderer::Texture aoTxt; 
        Renderer::Texture metallicRoughnessTxt; 
        Renderer::Texture normalTxt;
        Renderer::Texture emissionTxt;

        glm::vec3 albedo = glm::vec3(1.0f);
        float AO = 1.0f;
        glm::vec3 metallicRoughness = glm::vec3(0.0f, 1.0f, 0.0f);

        bool hasAlbedo = false;
        bool hasAO = false;
        bool hasMetallicRoughness = false;
    };
}
