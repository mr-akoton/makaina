#version 330 core

layout (location = 0) in vec3	in_position;
layout (location = 1) in vec2	in_noiseUV;

uniform	vec3	u_viewPosition;
uniform vec4	u_projection;


void	main()
{
	gl_Position = vec4(in_position, 1.0f);
}
