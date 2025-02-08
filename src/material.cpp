#include "material.hpp"

Renderer::Material::Material(Renderer::Texture &albedo, Renderer::Texture &arm, Renderer::Texture &normal, Renderer::Texture &depth)
: albedoTxt(albedo),
  armTxt(arm),
  normalTxt(normal),
  depthTxt(depth),
  hasAlbedo(true),
  hasArm(true),
  hasNormal(true),
  hasDepth(true) {}

Renderer::Material::Material(glm::vec3 albedo, glm::vec3 arm)
: albedo(albedo),
  arm(arm) {}

void Renderer::Material::Bind(Renderer::Shader &Shader) {
    if (hasAlbedo) albedoTxt.Bind(0, Shader, "mat.albedoTxt");
    if (hasArm) armTxt.Bind(1, Shader, "mat.armTxt");
    if (hasNormal) normalTxt.Bind(2, Shader, "mat.normalTxt");
    if (hasDepth) depthTxt.Bind(3, Shader, "mat.depthTxt");

    Shader.setVec3("mat.albedo", albedo);
    Shader.setVec3("mat.arm", arm);

    Shader.setBool("mat.hasAlbedo", hasAlbedo);
    Shader.setBool("mat.hasArm", hasArm);
    Shader.setBool("mat.hasNormal", hasNormal);
    Shader.setBool("mat.hasDepth", hasDepth);
}

void Renderer::Material::setAlbedo(glm::vec3 albedo) {
    this->albedo = albedo;
}
void Renderer::Material::setArm(glm::vec3 arm) {
    this->arm = arm;
}

void Renderer::Material::setAlbedoTexture(Renderer::Texture &albedo) {
    this->albedoTxt = albedo;
    hasAlbedo = true;
}
void Renderer::Material::setArmTexture(Renderer::Texture &arm) {
    this->armTxt = arm;
    hasArm = true;
}
void Renderer::Material::setNormalTexture(Renderer::Texture &normal) {
    this->normalTxt = normal;
    hasNormal = true;
}
void Renderer::Material::setDepthTexture(Renderer::Texture &depth) {
    this->depthTxt = depth;
    hasDepth = true;
}
