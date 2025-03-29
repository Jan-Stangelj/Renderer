#pragma once

#include "texture.hpp"
#include "shader.hpp"
#include "glm/glm.hpp"

#include <string>

namespace Renderer {
    class Material {
    public:
        Material(const std::string& albedo, const std::string& metallicRoughness);
        Material(const glm::vec3& albedo, const glm::vec3& metallicRoughness);
        Material() = default;

        void Bind(Renderer::Shader& Shader);

        void setAlbedoTexture(const std::string& albedo);
        void setMetallicRoughnessTexture(const std::string& metallicRoughness);
        void setNormalTexture(const std::string& normal);
        void setEmissionTexture(const std::string& emission);

        glm::vec3 albedo = glm::vec3(1.0f);
        glm::vec3 metallicRoughness = glm::vec3(0.0f, 1.0f, 0.0f);

    private:

        Renderer::Texture albedoTxt; 
        Renderer::Texture metallicRoughnessTxt; 
        Renderer::Texture normalTxt;
        Renderer::Texture emissionTxt;

        bool hasAlbedo = false;
        bool hasMetallicRoughness = false;
    };
}
