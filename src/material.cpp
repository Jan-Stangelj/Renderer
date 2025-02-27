#include "material.hpp"

int getColorChannels(std::string file);

Renderer::Material::Material(std::string albedo, std::string AO, std::string metallicRoughness) : hasAlbedo(true), hasAO(true), hasMetallicRoughness(true) {
    albedoTxt = Renderer::Texture(albedo, false);
    aoTxt = Renderer::Texture(AO, true);
    metallicRoughnessTxt = Renderer::Texture(metallicRoughness, true);
}

Renderer::Material::Material(glm::vec3 albedo, float AO, glm::vec3 metallicRoughness)
: albedo(albedo),
  AO(AO),
  metallicRoughness(metallicRoughness) {}

void Renderer::Material::Bind(Renderer::Shader Shader) {
    if (hasAlbedo) albedoTxt.Bind(0, Shader, "mat.albedoTxt");
    if (hasAO) aoTxt.Bind(1, Shader, "mat.aoTxt");
    if (hasMetallicRoughness) metallicRoughnessTxt.Bind(2, Shader, "mat.metallicRoughnessTxt");
    emissionTxt.Bind(4, Shader, "mat.emissionTxt");

    Shader.setVec3("mat.albedo", albedo);
    Shader.setFloat("mat.AO", AO);
    Shader.setVec3("mat.metallicRoughness", metallicRoughness);

    Shader.setBool("mat.hasAlbedo", hasAlbedo);
    Shader.setBool("mat.hasAO", hasAO);
    Shader.setBool("mat.hasMetallicRoughness", hasMetallicRoughness);
}

void Renderer::Material::setAlbedo(glm::vec3 albedo) {
    this->albedo = albedo;
}
void Renderer::Material::setAO(float AO) {
    this->AO = AO;
}
void Renderer::Material::setMetallicRoughness(glm::vec3 metallicRoughness) {
    this->metallicRoughness = metallicRoughness;
}

void Renderer::Material::setAlbedoTexture(std::string albedo) {
    albedoTxt.generate(albedo, false);
    hasAlbedo = true;
}
void Renderer::Material::setAOTexture(std::string AO) {
    aoTxt.generate(AO, true);
    hasAO = true;
}
void Renderer::Material::setMetallicRoughnessTexture(std::string metallicRoughness) {
    metallicRoughnessTxt.generate(metallicRoughness, true);
    hasMetallicRoughness = true;
}

void Renderer::Material::setEmissionTexture(std::string emission) {
    emissionTxt.generate(emission, false);
}