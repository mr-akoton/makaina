#version 330 core

layout (location = 0) in vec3	aPosition;
layout (location = 1) in vec3	aNormal;
layout (location = 2) in vec3	aColor;
layout (location = 3) in vec2	aTextureUV;

uniform float		glTime;

uniform vec3		color;
uniform float		level;
uniform mat4		model;
uniform mat4		cameraMatrix;

out	DATA
{
	vec3	normal;
	vec3	color;
	vec2	textureUV;
	mat4	projection;
}	data_out;

void	main()
{
	float wave = (
		sin(150.0 * aPosition.x + glTime )
		* cos(100.0 * aPosition.z + glTime)
		* 1.0);


	vec3	currentPosition = vec3(model * vec4(
		aPosition.x,
		level + wave,
		aPosition.z,
		1.0f
	));

	gl_Position = vec4(currentPosition, 1.0f);

	data_out.normal = aNormal;
	data_out.color = color;
	data_out.textureUV = aTextureUV;
	data_out.projection = cameraMatrix;
}
