#version 330 core

layout (location = 0) in vec3	l_position;
layout (location = 1) in vec3	l_normal;
layout (location = 2) in vec3	l_color;
layout (location = 3) in vec2	l_textureUV;

uniform mat4		model;
uniform mat4		cameraMatrix;
uniform	vec4		clipPlane;

uniform int			heightFactor;
uniform sampler2D	heightMap;

out DATA
{
	vec3	color;
	vec2	textureUV;
	mat4	projection;
}	data_out;

out float	gl_ClipDistance[1];

void	main()
{
	float	noiseValue = texture(heightMap, l_textureUV).r;
	float	height = pow(noiseValue, 8) * heightFactor;
	vec4	currentPosition = vec4(l_position.x, height, l_position.z, 1.0f);
	vec4	worldPosition = model * currentPosition;

	gl_ClipDistance[0] = dot(worldPosition, clipPlane);
	gl_Position = worldPosition;
	data_out.color = l_color;
	data_out.textureUV = l_textureUV;
	data_out.projection = cameraMatrix;
}
