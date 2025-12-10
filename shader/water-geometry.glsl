#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in DATA
{
	vec2	textureUV;
	vec3	color;
	vec3	cameraPosition;
	mat4	projection;
}	data_in[];

out vec3	color;
out	vec3	normal;
out	vec3	currentPosition;
out vec3	toCameraVector;


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

	for (int i = 0; i < 3; i++)
	{
		currentPosition = gl_in[i].gl_Position.xyz;
		gl_Position = data_in[i].projection * gl_in[i].gl_Position;
		color = data_in[i].color;
		normal = faceNormal;
		toCameraVector = normalize(data_in[i].cameraPosition - gl_in[i].gl_Position.xyz);
		EmitVertex();
	}

	EndPrimitive();
}
