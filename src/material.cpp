#include "material.hpp"

Renderer::Material::Material(std::string albedo, std::string AO, std::string roughness, std::string metallic) : hasAlbedo(true), hasAO(true), hasRoughness(true), hasMetallic(true) {
    albedoTxt = new Renderer::Texture(albedo, 16, 3, false);
    aoTxt = new Renderer::Texture(AO, 16, 1, true);
    roughnessTxt = new Renderer::Texture(roughness, 16, 1, true);
    metallicTxt = new Renderer::Texture(metallic, 16, 1, true);
}

Renderer::Material::Material(glm::vec3 albedo, float AO, float roughness, float metallic)
: albedo(albedo),
  AO(AO),
  roughness(roughness),
  metallic(metallic) {}

Renderer::Material::~Material() {
    delete(albedoTxt);
    delete(aoTxt);
    delete(roughnessTxt);
    delete(metallicTxt);
}

void Renderer::Material::Bind(Renderer::Shader Shader) {
    if (hasAlbedo) albedoTxt->Bind(0, Shader, "mat.albedoTxt");
    if (hasAO) aoTxt->Bind(1, Shader, "mat.aoTxt");
    if (hasRoughness) roughnessTxt->Bind(2, Shader, "mat.roughnessTxt");
    if (hasMetallic) metallicTxt->Bind(3, Shader, "mat.metallicTxt");

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
    if (hasAlbedo)
        albedoTxt->~Texture();
    albedoTxt = new Renderer::Texture(albedo, 16, 3, false);
    hasAlbedo = true;
}
void Renderer::Material::setAOTexture(std::string AO) {
    if (hasAO)
        aoTxt->~Texture();
    aoTxt = new Renderer::Texture(AO, 16, 1, true);
    hasAO = true;
}
void Renderer::Material::setRoughnessTexture(std::string roughness) {
    if (hasRoughness)
        roughnessTxt->~Texture();
    roughnessTxt = new Renderer::Texture(roughness, 16, 1, true);
    hasRoughness = true;
}
void Renderer::Material::setMetallicTexture(std::string metallic) {
    if (hasMetallic)
        metallicTxt->~Texture();
    metallicTxt = new Renderer::Texture(metallic, 16, 1, true);
    hasMetallic = true;
}
