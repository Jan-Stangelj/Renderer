#version 460 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gPBR;
uniform sampler2D gEmission;

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

uniform pointLight pointLights[128];
uniform spotLight spotLights[128];
uniform directionalLight dirLights[1];

uniform int numPointLights;
uniform int numSpotLights;
uniform int numDirLights;

uniform vec3 skybox;
uniform float exposure;

uniform vec3 camPos;

const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);

vec3 calcLight(vec3 albedo, float roughness, float metallic, vec3 normal, vec3 radiance, vec3 lightDir, vec3 fragPos);

vec3 ACESFitted(vec3 color);

void main() {
	vec3 resoult = vec3(0.0f);

	vec3 normal = texture(gNormal, texCoord).rgb;
	
    vec3 albedo = texture(gAlbedo, texCoord).rgb;
	float roughness =texture(gPBR, texCoord).g;
	float metallic = texture(gPBR, texCoord).b;

	vec3 fragPos = texture(gPosition, texCoord).rgb;

	for (int i = 0; i < numDirLights; i++) {
		directionalLight l = dirLights[i];

		resoult += calcLight(albedo, roughness, metallic, normal, l.color * l.intensity, -l.direction, fragPos);
	}
	for (int i = 0; i < numPointLights; i++) {
		pointLight l = pointLights[i];

		vec3 lightDir = l.position - fragPos;
		float distance = length(lightDir);
		float attenuation = l.strenght / pow(distance, distance);
		if (attenuation < 16.0/256.0)
			continue;

		resoult += calcLight(albedo, roughness, metallic, normal, l.color * attenuation, lightDir, fragPos);
	}
	for (int i = 0; i < numSpotLights; i++) {
		spotLight l = spotLights[i];

		vec3 lightDir = l.position - fragPos;
		float distance = length(lightDir);
		float attenuation = l.strenght / pow(distance, distance);
		if (attenuation < 16.0/256.0)
			continue;
		
		float theta = dot(normalize(lightDir), normalize(-l.direction));

		if (theta < l.outerCutoff)
			continue;

		float epsilon = l.cutoff - l.outerCutoff;
		float intensity = clamp((theta - l.outerCutoff) / epsilon, 0.0, 1.0);

		resoult += calcLight(albedo, roughness, metallic, normal, l.color * attenuation * intensity, lightDir, fragPos);
	}

	resoult += skybox * albedo;
	resoult += texture(gEmission, texCoord).rgb;

	resoult = ACESFitted(resoult * exposure);
	resoult = pow(resoult, vec3(1.0/2.2));

	FragColor.rgb = resoult;

}

// --------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------

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

vec3 calcLight(vec3 albedo, float roughness, float metallic, vec3 normal, vec3 radiance, vec3 lightDir, vec3 fragPos) {

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

mat3x3 ACESInputMat = mat3x3 (
	0.59719, 0.35458, 0.04823,
	0.07600, 0.90834, 0.01566,
	0.02840, 0.13383, 0.83777
);

// ODT_SAT => XYZ => D60_2_D65 => sRGB
mat3x3 ACESOutputMat = mat3x3 (
	 1.60475, -0.53108, -0.07367,
	-0.10208,  1.10813, -0.00605,
	-0.00327, -0.07276,  1.07602
);

vec3 RRTAndODTFit(vec3 v) {
	vec3 a = v * (v + 0.0245786f) - 0.000090537f;
	vec3 b = v * (0.983729f * v + 0.4329510f) + 0.238081f;
	return a / b;
}

vec3 ACESFitted(vec3 color) {
	color = transpose(ACESInputMat) * color;
	color = RRTAndODTFit(color);
	color = transpose(ACESOutputMat) * color;
	color = clamp(color, 0, 1);
	return color;
}