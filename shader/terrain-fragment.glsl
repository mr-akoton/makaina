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


vec3	getColorBySlope()
{
	// 0 is flat, 1 is vertical
	float	slope = 1.0f - normal.y;

	if (slope < 0.2f && height > 10)
	{
		return vec3(1.0f, 0.0f, 0.0f);
	}
	else
	{
		return vec3(1.0f, 1.0f, 1.0f);
	}
}

vec4	directionLight()
{
	float	ambienLight = 0.2f;

	vec3	norm = normalize(normal);
	vec3	lightDirection = normalize(lightPosition);
	float	diffuse = max(dot(norm, lightDirection), 0.0f);

	return vec4(getColorBySlope() * lightColor, 1.0f) * (diffuse + ambienLight);
}

void main()
{
	FragColor = directionLight();
}
