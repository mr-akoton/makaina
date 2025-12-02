#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in DATA
{
	vec3	normal;
	vec3	color;
	vec2	textureUV;
	mat4	projection;
}	data_in[];

out vec3	color;


void	main()
{
	gl_Position = data_in[0].projection * gl_in[0].gl_Position;
	color = data_in[0].color;
	EmitVertex();

	gl_Position = data_in[1].projection * gl_in[1].gl_Position;
	color = data_in[1].color;
	EmitVertex();

	gl_Position = data_in[2].projection * gl_in[2].gl_Position;
	color = data_in[2].color;
	EmitVertex();

	EndPrimitive();
}