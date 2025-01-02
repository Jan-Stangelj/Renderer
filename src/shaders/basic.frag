#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

// texture sampler

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D ambientOcclusion;
	float smoothnes;
};

struct PointLight {
	vec3 position;

	vec3 color;
	float strenght;
	float ambient;
};

uniform Material mat;
uniform PointLight light;

uniform vec3 camPos;



void main()
{
	vec3 ambient = light.color * light.ambient * (texture(mat.diffuse, TexCoord).xyz * texture(mat.ambientOcclusion, TexCoord).xxx);

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * ((light.color * light.strenght) / pow(distance(light.position, FragPos), 2))  * (texture(mat.diffuse, TexCoord).xyz * texture(mat.ambientOcclusion, TexCoord).xxx);

	vec3 viewDir = normalize(camPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.smoothnes);
	vec3 specular = spec * ((light.color * light.strenght) / pow(distance(light.position, FragPos), 2)) * texture(mat.specular, TexCoord).xxx;  

	vec3 result = (ambient + diffuse + specular);

	FragColor = vec4(result, 1.0);
}