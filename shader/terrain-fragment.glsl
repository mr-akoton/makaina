#version 330 core

uniform vec3		lightPosition;
uniform vec3		lightColor;
uniform vec3		cameraPosition;
uniform float		heightFactor;
uniform sampler2D	diffuse0;
uniform sampler2D	specular0;

in float	height;
in vec3		normal;
in vec3		color;
in vec2		textureUV;

out vec4	FragColor;


vec4	directionLight()
{
	float	ambienLight = 0.2f;

	vec3	norm = normalize(normal);
	vec3	lightDirection = normalize(lightPosition);
	float	diffuse = max(dot(norm, lightDirection), 0.0f);

	return vec4(color * lightColor, 1.0f) * (diffuse + ambienLight);
}

void main()
{
	FragColor = directionLight();
}
