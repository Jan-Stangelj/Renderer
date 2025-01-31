#include "lighting.hpp"

void Renderer::setLight(Renderer::Shader &Shader, Renderer::PointLight &light, int index) {
        Shader.setVec3("pointlight["+std::to_string(index)+"].position", light.Position);
        Shader.setVec3("pointlight["+std::to_string(index)+"].color", light.Color);
        Shader.setFloat("pointlight["+std::to_string(index)+"].strenght", light.Strength);
        Shader.setFloat("pointlight["+std::to_string(index)+"].ambient", light.Ambient);
}

void Renderer::setLight(Renderer::Shader &Shader, Renderer::DirectionLight &light, int index) {
        Shader.setVec3("dirlight["+std::to_string(index)+"].direction", light.Direction);
        Shader.setVec3("dirlight["+std::to_string(index)+"].color", light.Color);
        Shader.setFloat("dirlight["+std::to_string(index)+"].intensity", light.Intensity);
        Shader.setFloat("dirlight["+std::to_string(index)+"].ambient", light.Ambient);
}