#version 330 core

layout (location = 0) in vec3	aPosition;
layout (location = 1) in vec3	aNormal;
layout (location = 2) in vec3	aColor;
layout (location = 3) in vec2	aTextureUV;

uniform mat4		model;
uniform mat4		cameraMatrix;
uniform float		heightFactor;
uniform sampler2D	heightMap;

out	DATA
{
	float	noiseValue;
	vec3	normal;
	vec3	color;
	vec2	textureUV;
	mat4	projection;
}	data_out;

void	main()
{
	float	noiseValue = texture(heightMap, aTextureUV).r;
	float	height = pow(noiseValue, 8) * heightFactor;

	vec3	currentPosition = vec3(model * vec4(
		aPosition.x,
		height,
		aPosition.z, 1.0f
	));

	gl_Position = vec4(currentPosition, 1.0f);

	data_out.noiseValue = noiseValue;
	data_out.normal = aNormal;
	data_out.color = aColor;
	data_out.textureUV = aTextureUV;
	data_out.projection = cameraMatrix;
}
