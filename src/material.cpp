#include "material.hpp"

void Renderer::Material::Bind(Renderer::Shader &Shader) {
    Diffuse.Bind(0, Shader, "mat.albedoTxt");
    Arm.Bind(1, Shader, "mat.armTxt");
}