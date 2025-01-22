#include "lighting.hpp"

void Renderer::setMaterial(Renderer::Material &Material) {
    Material.Diffuse.Bind(0, Material.Shader, "mat.diffuse");
    Material.Specular.Bind(1, Material.Shader, "mat.specular");
    Material.AO.Bind(2, Material.Shader, "mat.ambientOcclusion");
    Material.Shader.setFloat("mat.smoothnes", Material.Smoothnes);
}

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