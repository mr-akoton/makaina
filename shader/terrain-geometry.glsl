#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in	DATA
{
	vec3	normal;
	vec3	color;
	vec2	textureUV;
	mat4	projection;
}	data_in[];

out float	height;
out vec3 	normal;
out vec3 	color;
out vec2 	textureUV;


vec3	getNormal(vec3 a, vec3 b, vec3 c)
{
	return normalize(cross(b - a, c - a));
}

void	main()
{
	vec3	norm = getNormal(
		gl_in[0].gl_Position.xyz,
		gl_in[1].gl_Position.xyz,
		gl_in[2].gl_Position.xyz
	);

	gl_Position = data_in[0].projection * gl_in[0].gl_Position;
	height = gl_in[0].gl_Position.y;
	normal = norm;
	color = data_in[0].color;
	textureUV = data_in[0].textureUV;
	EmitVertex();

	gl_Position = data_in[1].projection * gl_in[1].gl_Position;
	height = gl_in[1].gl_Position.y;
	normal = norm;
	color = data_in[1].color;
	textureUV = data_in[1].textureUV;
	EmitVertex();

	gl_Position = data_in[2].projection * gl_in[2].gl_Position;
	height = gl_in[2].gl_Position.y;
	normal = norm;
	color = data_in[2].color;
	textureUV = data_in[2].textureUV;
	EmitVertex();

	EndPrimitive();
}