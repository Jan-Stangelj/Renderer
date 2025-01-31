#include "material.hpp"

void Renderer::setMaterial(Renderer::Material &Material) {
    Material.Diffuse.Bind(0, Material.Shader, "mat.diffuse");
    Material.Specular.Bind(1, Material.Shader, "mat.specular");
    Material.AO.Bind(2, Material.Shader, "mat.ambientOcclusion");
    Material.Shader.setFloat("mat.smoothnes", Material.Smoothnes);
}