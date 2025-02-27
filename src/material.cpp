#include "material.hpp"

int getColorChannels(std::string file);

Renderer::Material::Material(std::string albedo, std::string AO, std::string roughness, std::string metallic) : hasAlbedo(true), hasAO(true), hasRoughness(true), hasMetallic(true) {
    albedoTxt = Renderer::Texture(albedo, false);
    aoTxt = Renderer::Texture(AO, true);
    roughnessTxt = Renderer::Texture(roughness, true);
    metallicTxt = Renderer::Texture(metallic, true);
}

Renderer::Material::Material(glm::vec3 albedo, float AO, float roughness, float metallic)
: albedo(albedo),
  AO(AO),
  roughness(roughness),
  metallic(metallic) {}

void Renderer::Material::Bind(Renderer::Shader Shader) {
    if (hasAlbedo) albedoTxt.Bind(0, Shader, "mat.albedoTxt");
    if (hasAO) aoTxt.Bind(1, Shader, "mat.aoTxt");
    if (hasRoughness) roughnessTxt.Bind(2, Shader, "mat.roughnessTxt");
    if (hasMetallic) metallicTxt.Bind(3, Shader, "mat.metallicTxt");
    emissionTxt.Bind(4, Shader, "mat.emissionTxt");

    Shader.setVec3("mat.albedo", albedo);
    Shader.setFloat("mat.AO", AO);
    Shader.setFloat("mat.roughness", roughness);
    Shader.setFloat("mat.metallic", metallic);

    Shader.setBool("mat.hasAlbedo", hasAlbedo);
    Shader.setBool("mat.hasAO", hasAO);
    Shader.setBool("mat.hasRoughness", hasRoughness);
    Shader.setBool("mat.hasMetallic", hasMetallic);
}

void Renderer::Material::setAlbedo(glm::vec3 albedo) {
    this->albedo = albedo;
}
void Renderer::Material::setAO(float AO) {
    this->AO = AO;
}
void Renderer::Material::setRoughness(float roughness) {
    this->roughness = roughness;
}
void Renderer::Material::setMetallic(float metallic) {
    this->metallic = metallic;
}

void Renderer::Material::setAlbedoTexture(std::string albedo) {
    albedoTxt.generate(albedo, false);
    hasAlbedo = true;
}
void Renderer::Material::setAOTexture(std::string AO) {
    aoTxt.generate(AO, true);
    hasAO = true;
}
void Renderer::Material::setRoughnessTexture(std::string roughness) {
    roughnessTxt.generate(roughness, true);
    hasRoughness = true;
}
void Renderer::Material::setMetallicTexture(std::string metallic) {
    metallicTxt.generate(metallic, true);
    hasMetallic = true;
}

void Renderer::Material::setEmissionTexture(std::string emission) {
    emissionTxt.generate(emission, false);
}