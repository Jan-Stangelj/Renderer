#include "lighting.hpp"

void Renderer::PointLight::Bind(Renderer::Shader &Shader, int index) {
        Shader.setVec3("pointlight["+std::to_string(index)+"].position", Position);
        Shader.setVec3("pointlight["+std::to_string(index)+"].color", Color);
        Shader.setFloat("pointlight["+std::to_string(index)+"].strenght", Strength);
}

void Renderer::DirectionLight::Bind(Renderer::Shader &Shader, int index) {
        Shader.setVec3("dirlight["+std::to_string(index)+"].direction", Direction);
        Shader.setVec3("dirlight["+std::to_string(index)+"].color", Color);
        Shader.setFloat("dirlight["+std::to_string(index)+"].intensity", Intensity);
}