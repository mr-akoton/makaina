#version 330 core

layout (location = 0) in vec3	l_position;
layout (location = 1) in vec3	l_normal;
layout (location = 2) in vec3	l_color;
layout (location = 3) in vec2	l_textureUV;

uniform mat4		model;
uniform vec3		color;
uniform vec3		cameraPosition;
uniform mat4		cameraMatrix;
uniform float		height;
uniform float		globalTime;

uniform sampler2D	heightMap;

out DATA
{
	vec2	textureUV;
	vec3	color;
	vec3	cameraPosition;
	mat4	projection;
}	data_out;


void	main()
{
	float	noiseValue = texture(heightMap, l_textureUV).r;
	float	wave = cos(-20.0f * noiseValue + globalTime) * 1.0f;
	
	gl_Position = model * vec4(
		l_position.x,
		l_position.y + wave,
		l_position.z,
		1.0f
	);

	data_out.color = color;
	data_out.textureUV = l_textureUV;
	data_out.cameraPosition = cameraPosition;
	data_out.projection = cameraMatrix;
}
