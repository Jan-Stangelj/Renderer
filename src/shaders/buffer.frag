#version 460 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gAlbedo;
layout (location = 3) out vec3 gPBR;
layout (location = 4) out vec3 gEmission;

in vec2 texCoord;
in vec3 fragPos;
in mat3 TBN;


struct material {
	sampler2D albedoTxt;
	sampler2D metallicRoughnessTxt;
	sampler2D normalTxt;
	sampler2D emissionTxt;

	vec3 albedo;
	vec3 metallicRoughness;

	bool hasAlbedo, hasMetallicRoughness;
};

uniform material mat;

void main() {
	if (texture(mat.albedoTxt, texCoord).w == 0)
		discard;

	vec3 normal = texture(mat.normalTxt, texCoord).rgb;
	normal = normal * 2.0 - 1.0;
	normal = normalize(TBN * normal);
	
    vec3 albedo = mat.hasAlbedo ? texture(mat.albedoTxt, texCoord).rgb : vec3(mat.albedo);
	float roughness = mat.hasMetallicRoughness ? texture(mat.metallicRoughnessTxt, texCoord).g : mat.metallicRoughness.g;
	float metallic = mat.hasMetallicRoughness ? texture(mat.metallicRoughnessTxt, texCoord).b : mat.metallicRoughness.b;

	gPosition = fragPos;
	gNormal = normal;
	gAlbedo = pow(albedo, vec3(2.2));
	gPBR = vec3(0, roughness, metallic);
	gEmission = pow(texture(mat.emissionTxt, texCoord).rgb, vec3(2.2));
}