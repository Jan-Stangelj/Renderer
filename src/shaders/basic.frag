#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;


struct material {
	sampler2D albedoTxt;
	sampler2D armTxt;
	sampler2D normalTxt;
	sampler2D depthTxt;
	vec3 albedo;
	vec3 arm;
	bool hasAlbedo;
	bool hasArm;
	bool hasNormal;
	bool hasDepth;
};


struct pointLight {
	vec3 position;
	vec3 color;
	float strenght;
};


struct directionalLight {
	vec3 direction;
	vec3 color;
	float intensity;
};

uniform material mat;

uniform pointLight pointLights[32];
uniform directionalLight dirLights[4];
uniform int numPointLights;
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

vec3 calcPointLight(vec3 albedo, vec3 arm, vec3 normal, pointLight light) {
	float metallic = arm.z;
	float roughness = arm.y;

    vec3 N = normal;
    vec3 V = normalize(camPos - fragPos);

	vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

	// calculate per-light radiance
	vec3 L = normalize(light.position - fragPos);
	vec3 H = normalize(V + L);
	float distance = length(light.position - fragPos);
	float attenuation = light.strenght / pow(distance, distance);
	vec3 radiance = light.color * attenuation;

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

vec3 calcDirectionalLight(vec3 albedo, vec3 arm, vec3 normal, directionalLight light) {
	float metallic = arm.z;
	float roughness = arm.y;

    vec3 N = normal;
    vec3 V = normalize(camPos - fragPos);

	vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

	// calculate per-light radiance
	vec3 L = normalize(-light.direction);
	vec3 H = normalize(V + L);
	vec3 radiance = light.color * light.intensity;

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
	vec3 resoult = vec3(0.0f);
    vec3 albedo = mat.hasAlbedo ? texture(mat.albedoTxt, texCoord).xyz : mat.albedo;
    vec3 arm = mat.hasArm ? texture(mat.armTxt, texCoord).xyz : mat.arm;

	for (int i = 0; i < numDirLights; ++i) {
		resoult += calcDirectionalLight(albedo, arm, normal, dirLights[i]);
	}
	for (int i = 0; i < numPointLights; ++i) {
		resoult += calcPointLight(albedo, arm, normal, pointLights[i]);
	}
	resoult += vec3(0.03) * albedo * arm.x;
	FragColor.rgb = pow(resoult, vec3(1.0/2.2));
}
