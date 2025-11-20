#version 330 core

layout (location = 0) in vec3	aPosition;
layout (location = 1) in vec3	aNormal;
layout (location = 2) in vec3	aColor;
layout (location = 3) in vec2	aTextureUV;

uniform mat4		model;
uniform mat4		cameraMatrix;
uniform vec2		terrainSize;
uniform float		heightFactor;
uniform sampler2D	heightMap;

out vec3	currentPosition;
out vec3	normal;
out vec3	color;
out vec2	textureUV;


vec3	getNormal()
{
	vec2	textureSize = 1.0 / textureSize(heightMap, 0);

	float	heightL = texture(heightMap, aTextureUV + vec2(-textureSize.x,0.0)).r;
	float	heightR = texture(heightMap, aTextureUV + vec2(textureSize.x,0.0)).r;
	float	heightD = texture(heightMap, aTextureUV + vec2(0.0,-textureSize.y)).r;
	float	heightU = texture(heightMap, aTextureUV + vec2(0.0,textureSize.y)).r;

	float	stepX = terrainSize.x * textureSize.x;
	float	stepZ = terrainSize.y * textureSize.y;

	vec3	tangentX = vec3(stepX * 2.0, (heightR - heightL) * heightFactor, 0.0);
	vec3	tangentZ = vec3(0.0, (heightU - heightD) * heightFactor, stepZ * 2.0);

	return normalize(cross(tangentZ, tangentX));
}

void main()
{
	float	height = texture(heightMap, aTextureUV).r;

	currentPosition = vec3(model * vec4(aPosition, 1.0f));
	currentPosition.y += height * heightFactor;

	gl_Position = cameraMatrix * vec4(currentPosition, 1.0f);

	normal = getNormal();
	color = aColor;
	textureUV = aTextureUV;
}
