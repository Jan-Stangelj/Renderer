#pragma once

#include "shader.hpp"
#include <string>

namespace Renderer {

    class PointLight {
    public:

        PointLight(const glm::vec3& position, const glm::vec3& color, float strength)
        : Position(position), 
          Color(color), 
          Strength(strength) {}

          void Bind(Renderer::Shader &Shader, int index);

        glm::vec3 Position;
        glm::vec3 Color;
        float Strength;
    };

    class DirectionLight {
    public:

        DirectionLight(const glm::vec3& direction, const glm::vec3& color, float intensity)
        : Direction(direction), 
        Color(color), 
        Intensity(intensity) {}

        void Bind(Renderer::Shader &Shader, int index);

        glm::vec3 Direction;
        glm::vec3 Color;
        float Intensity;
    };

    class SpotLight {
    public:

        SpotLight(const glm::vec3& position, const glm::vec3& color, float strength, const glm::vec3& direction, float cutoff, float outerCutoff)
        : position(position),
        color(color),
        strength(strength),
        direction(direction),
        cutoff(cutoff),
        outerCutoff(outerCutoff) {}

        void Bind(Renderer::Shader &Shader, int index);

        glm::vec3 position;
        glm::vec3 color;
        float strength;
        glm::vec3 direction;
        float cutoff;
        float outerCutoff;

    };
}