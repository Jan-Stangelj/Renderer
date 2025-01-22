// Fragment shader for basic lighting
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

// Material properties including textures and surface characteristics
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D ambientOcclusion;
	float smoothnes;
};

// Point light properties
struct PointLight {
	vec3 position;
	vec3 color;
	float strenght;
	float ambient;
};

// Directional light properties
struct DirectionalLight {
	vec3 direction;
	vec3 color;
	float ambient;
	float intensity;
};

uniform Material mat;

uniform PointLight pointlight[32];
uniform DirectionalLight dirlight[4];
uniform int numPointLights;
uniform int numDirLights;

uniform vec3 camPos;

// Calculate point light contribution including ambient, diffuse and specular components
vec3 calcPointLight(Material mat, PointLight light, vec3 camPos) {
	vec3 ambient = light.color * light.ambient * (texture(mat.diffuse, TexCoord).xyz * texture(mat.ambientOcclusion, TexCoord).xxx);

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * ((light.color * light.strenght) / pow(distance(light.position, FragPos), 2))  * (texture(mat.diffuse, TexCoord).xyz * texture(mat.ambientOcclusion, TexCoord).xxx);

	//vec3 viewDir = normalize(camPos - FragPos);
	//vec3 reflectDir = reflect(-lightDir, norm);

	vec3 viewDir    = normalize(camPos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), mat.smoothnes);
	vec3 specular = spec * ((light.color * light.strenght) / pow(distance(light.position, FragPos), 2)) * texture(mat.specular, TexCoord).xxx;  

	return (ambient + diffuse + specular);
}

vec3 calcDirectionalLight(Material mat, DirectionalLight light, vec3 camPos) {
	vec3 ambient = light.color * light.ambient * (texture(mat.diffuse, TexCoord).xyz * texture(mat.ambientOcclusion, TexCoord).xxx);

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * (light.color * light.intensity) * (texture(mat.diffuse, TexCoord).xyz * texture(mat.ambientOcclusion, TexCoord).xxx);

	vec3 viewDir = normalize(camPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.smoothnes);
	vec3 specular = spec * (light.color * light.intensity) * texture(mat.specular, TexCoord).xxx;  

	return (ambient + diffuse + specular);
}void main()
{
	vec3 resoult = vec3(0.0f);
	for (int i = 0; i < numDirLights; ++i) {
		resoult += calcDirectionalLight(mat, dirlight[i], camPos);
	}
	for (int i = 0; i < numPointLights; ++i) {
		resoult += calcPointLight(mat, pointlight[i], camPos);
	}
	FragColor.rgb = pow(resoult, vec3(1.0/2.2));
}