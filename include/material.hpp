#pragma once

#include <texture.hpp>
#include <shader.hpp>
#include <glm/glm.hpp>

namespace Renderer {
    class Material {
    public:
        Material(Renderer::Texture &albedo, Renderer::Texture &arm, Renderer::Texture &normal, Renderer::Texture &depth);
        Material(glm::vec3 albedo, glm::vec3 arm);

        void Bind(Renderer::Shader &shader);

        void setAlbedo(glm::vec3 albedo);
        void setArm(glm::vec3 arm);

        void setAlbedoTexture(Renderer::Texture &albedo);
        void setArmTexture(Renderer::Texture &arm);
        void setNormalTexture(Renderer::Texture &normal);
        void setDepthTexture(Renderer::Texture &depth);

    private:
        Renderer::Texture albedoTxt;
        Renderer::Texture armTxt;
        Renderer::Texture normalTxt;;
        Renderer::Texture depthTxt;
        glm::vec3 albedo;
        glm::vec3 arm;
        bool hasAlbedo = false;
        bool hasArm = false;
        bool hasNormal = false;
        bool hasDepth = false;
    };
}
