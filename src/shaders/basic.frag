#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 fragPos;
in mat3 TBN;


struct material {
	sampler2D albedoTxt;
	sampler2D aoTxt;
	sampler2D metallicRoughnessTxt;
	sampler2D normalTxt;
	sampler2D emissionTxt;

	vec3 albedo;
	float AO;
	vec3 metallicRoughness;

	bool hasAlbedo, hasAO, hasMetallicRoughness;
};


struct pointLight {
	vec3 position;
	vec3 color;
	float strenght;
};

struct spotLight {
	vec3 position;
	vec3 color;
	float strenght;

	vec3 direction;
	float cutoff; 
	float outerCutoff;
};


struct directionalLight {
	vec3 direction;
	vec3 color;
	float intensity;
};

uniform material mat;

uniform pointLight pointLights[32];
uniform spotLight spotLights[32];
uniform directionalLight dirLights[4];

uniform int numPointLights;
uniform int numSpotLights;
uniform int numDirLights;

uniform vec3 camPos;

const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 calcLight(vec3 albedo, float roughness, float metallic, vec3 normal, vec3 radiance, vec3 lightDir) {

    vec3 N = normal;
    vec3 V = normalize(camPos - fragPos);

	vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

	// calculate per-light radiance
	vec3 L = normalize(lightDir);
	vec3 H = normalize(V + L);

	// Cook-Torrance BRDF
	float NDF = DistributionGGX(N, H, roughness);
	float G   = GeometrySmith(N, V, L, roughness);
	vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
		
	vec3 numerator    = NDF * G * F;
	float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
	vec3 specular = numerator / denominator;
	
	// kS is equal to Fresnel
	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;

	kD *= 1.0 - metallic;

	// scale light by NdotL
	float NdotL = max(dot(N, L), 0.0);  

	return (kD * albedo / PI + specular) * radiance * NdotL;
}

void main() {
	if (texture(mat.albedoTxt, texCoord).w == 0)
		discard;

	vec3 normal = texture(mat.normalTxt, texCoord).rgb;
	normal = normal * 2.0 - 1.0;
	normal = normalize(TBN * normal);
	
	vec3 resoult = vec3(0.0f);
    vec3 albedo = mat.hasAlbedo ? texture(mat.albedoTxt, texCoord).xyz : mat.albedo;
    float AO = mat.hasAO ? texture(mat.aoTxt, texCoord).x : mat.AO;
	float roughness = mat.hasMetallicRoughness ? texture(mat.metallicRoughnessTxt, texCoord).g : mat.metallicRoughness.g;
	float metallic = mat.hasMetallicRoughness ? texture(mat.metallicRoughnessTxt, texCoord).b : mat.metallicRoughness.b;

	for (int i = 0; i < numDirLights; i++) {
		directionalLight l = dirLights[i];

		resoult += calcLight(albedo, roughness, metallic, normal, l.color * l.intensity, -l.direction);
	}
	for (int i = 0; i < numPointLights; i++) {
		pointLight l = pointLights[i];

		float distance = length(l.position - fragPos);
		float attenuation = l.strenght / pow(distance, distance);
		if (attenuation < 0.025)
			continue;

		resoult += calcLight(albedo, roughness, metallic, normal, l.color * attenuation, l.position - fragPos);
	}
	for (int i = 0; i < numSpotLights; i++) {
		spotLight l = spotLights[i];

		vec3 lightDir = l.position - fragPos;
		float distance = length(lightDir);
		float attenuation = l.strenght / pow(distance, distance);
		if (attenuation < 0.025)
			continue;
		
		float theta = dot(normalize(lightDir), normalize(-l.direction));

		if (theta < l.outerCutoff)
			continue;

		float epsilon = l.cutoff - l.outerCutoff;
		float intensity = clamp((theta - l.outerCutoff) / epsilon, 0.0, 1.0);

		resoult += calcLight(albedo, roughness, metallic, normal, l.color * attenuation * intensity, lightDir);
	}

	resoult += vec3(0.03) * albedo * AO;
	resoult += texture(mat.emissionTxt, texCoord).rgb;

	FragColor.rgb = pow(resoult, vec3(1.0/2.2));
}