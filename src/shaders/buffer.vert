#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;

out vec2 texCoord;
out vec3 fragPos;
out mat3 TBN;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model  * vec4(aPos, 1.0);
	texCoord = vec2(aTexCoord.x, aTexCoord.y);
	fragPos = vec3(model * vec4(aPos, 1.0));

	vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
	vec3 B = cross(T, N);
	TBN = mat3(T, B, N);
}