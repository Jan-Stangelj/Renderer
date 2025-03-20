#include "material.hpp"

int getColorChannels(std::string file);

Renderer::Material::Material(std::string albedo, std::string metallicRoughness) : hasAlbedo(true), hasMetallicRoughness(true) {
    albedoTxt = Renderer::Texture(albedo, false);
    metallicRoughnessTxt = Renderer::Texture(metallicRoughness, true);
}

Renderer::Material::Material(glm::vec3 albedo, glm::vec3 metallicRoughness)
: albedo(albedo),
  metallicRoughness(metallicRoughness) {}

void Renderer::Material::Bind(Renderer::Shader Shader) {
    if (hasAlbedo) albedoTxt.Bind(0, Shader, "mat.albedoTxt");
    if (hasMetallicRoughness) metallicRoughnessTxt.Bind(2, Shader, "mat.metallicRoughnessTxt");
    normalTxt.Bind(3, Shader, "mat.normalTxt");
    emissionTxt.Bind(4, Shader, "mat.emissionTxt");

    Shader.setVec3("mat.albedo", albedo);
    Shader.setVec3("mat.metallicRoughness", metallicRoughness);

    Shader.setBool("mat.hasAlbedo", hasAlbedo);
    Shader.setBool("mat.hasMetallicRoughness", hasMetallicRoughness);
}

void Renderer::Material::setAlbedo(glm::vec3 albedo) {
    this->albedo = albedo;
}
void Renderer::Material::setMetallicRoughness(glm::vec3 metallicRoughness) {
    this->metallicRoughness = metallicRoughness;
}

void Renderer::Material::setAlbedoTexture(std::string albedo) {
    albedoTxt.generate(albedo, false);
    hasAlbedo = true;
}
void Renderer::Material::setMetallicRoughnessTexture(std::string metallicRoughness) {
    metallicRoughnessTxt.generate(metallicRoughness, true);
    hasMetallicRoughness = true;
}
void Renderer::Material::setNormalTexture(std::string normal) {
    normalTxt.generate(normal, true);
}

void Renderer::Material::setEmissionTexture(std::string emission) {
    emissionTxt.generate(emission, false);
}