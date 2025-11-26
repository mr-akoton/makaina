#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;
              
in	DATA
{
	float	noiseValue;
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

float	getAverageHeight(float height1, float height2, float height3)
{
	return (height1 + height2 + height3) / 3.0f;
}

void	main()
{
	vec3	norm = getNormal(
		gl_in[0].gl_Position.xyz,
		gl_in[1].gl_Position.xyz,
		gl_in[2].gl_Position.xyz
	);

	float	averageHeight = getAverageHeight(
		data_in[0].noiseValue,
		data_in[1].noiseValue,
		data_in[2].noiseValue
	);

	gl_Position = data_in[0].projection * gl_in[0].gl_Position;
	height = averageHeight;
	normal = norm;
	color = data_in[0].color;
	textureUV = data_in[0].textureUV;
	EmitVertex();

	gl_Position = data_in[1].projection * gl_in[1].gl_Position;
	height = averageHeight;
	normal = norm;
	color = data_in[1].color;
	textureUV = data_in[1].textureUV;
	EmitVertex();

	gl_Position = data_in[2].projection * gl_in[2].gl_Position;
	height = averageHeight;
	normal = norm;
	color = data_in[2].color;
	textureUV = data_in[2].textureUV;
	EmitVertex();

	EndPrimitive();
}