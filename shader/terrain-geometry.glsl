#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in DATA
{
	vec3	color;
	vec2	textureUV;
	mat4	projection;
}	data_in[];

out vec3	color;
out	vec3	normal;
out	vec3	currentPosition;


vec3	getNormal(vec3 point1, vec3 point2, vec3 point3)
{
	return normalize(cross(point2 - point1, point3 - point1));
}

void	main()
{
	vec3	faceNormal = getNormal(
		gl_in[0].gl_Position.xyz,
		gl_in[1].gl_Position.xyz,
		gl_in[2].gl_Position.xyz
	);

	currentPosition = gl_in[0].gl_Position.xyz;
	gl_Position = data_in[0].projection * gl_in[0].gl_Position;
	color = data_in[0].color;
	normal = faceNormal;
	EmitVertex();

	currentPosition = gl_in[1].gl_Position.xyz;
	gl_Position = data_in[1].projection * gl_in[1].gl_Position;
	color = data_in[1].color;
	normal = faceNormal;
	EmitVertex();

	currentPosition = gl_in[2].gl_Position.xyz;
	gl_Position = data_in[2].projection * gl_in[2].gl_Position;
	color = data_in[2].color;
	normal = faceNormal;
	EmitVertex();

	EndPrimitive();
}
