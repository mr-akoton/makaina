#version 330 core

uniform sampler2D	diffuse0;
uniform sampler2D	specular0;
uniform vec3		lightPos;
uniform vec3		lightColor;
uniform vec3		camPos;

in vec3	currentPos;
in vec3	normal;
in vec3	color;
in vec2	texUV;

out vec4	FragColor;


vec4	directionLight()
{
	float	ambienLight = 0.2f;
	
	vec3	norm = normalize(normal);
	vec3	lightDirection = normalize(lightPos);
	float	diffuse = max(dot(norm, lightDirection), 0.0f);

	return vec4(color * lightColor, 0.1f) * (diffuse + ambienLight);
}

void main()
{
	FragColor = directionLight();
}
