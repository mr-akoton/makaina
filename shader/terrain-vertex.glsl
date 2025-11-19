#version 330 core

layout (location = 0) in vec3	aPosition;
layout (location = 1) in vec3	aNormal;
layout (location = 2) in vec3	aColor;
layout (location = 3) in vec2	aTextureUV;

uniform mat4		model;
uniform mat4		cameraMatrix;
uniform sampler2D	heightMap;

out vec3	currentPosition;
out vec3	normal;
out vec3	color;
out vec2	textureUV;


vec3	getNormal(vec2 uv, float heightScale)
{
	vec3	textureSize = 1.0 / textureSize(heightMap, 0);

	float	heightL = texture(heightMap, uv + vec2(-textureSize.x, 0.0)).r;
	float	heightR = texture(heightMap, uv + vec2(textureSize.x, 0.0)).r;
	float	heightD = texture(heightMap, uv + vec2(0.0, -textureSize.y)).r;
	float	heightU = texture(heightMap, uv + vec2(0.0, textureSize.y)).r;

	float	stepX = terrainSize.x * textureSize.x;
	float	stepY = terrainSize.y * textureSize.y;

	vec3	tangentX = vec3(stepX * 2.0);
}

void main()
{
	float	height = texture(heightMap, aTextureUV).r;

	currentPosition = vec3(model * vec4(aPosition, 1.0f));
	currentPosition.y += height * 500.0f;

	gl_Position = cameraMatrix * vec4(currentPosition, 1.0f);

	normal = aNormal;
	color = aColor;
	textureUV = aTextureUV;
}
