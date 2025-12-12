#version 330 core


layout (location = 0) in vec3	l_position;
layout (location = 1) in vec3	l_normal;
layout (location = 2) in vec3	l_color;
layout (location = 3) in vec2	l_textureUV;

uniform mat4		u_model;
uniform mat4		u_projection;
uniform sampler2D	u_heightMap;
uniform int			u_heightScale;

out vec3	pass_color;
out vec3	pass_normal;
out	vec3	pass_vertexPosition;

/* ========================================================================== */
/*                                   HEIGHT                                   */
/* ========================================================================== */

float	getHeight(vec2 coord)
{
	return texture(u_heightMap, coord).r;
}

/* ========================================================================== */
/*                                    MAIN                                    */
/* ========================================================================== */

void	main()
{
	float	height = pow(getHeight(l_textureUV), 8);
	vec4	vertexPosition = u_model * vec4(
		l_position.x,
		height * u_heightScale,
		l_position.z,
		1.0f
	);

	gl_Position = u_projection * vertexPosition;
	pass_color = l_color;
	pass_normal = l_normal;
	pass_vertexPosition = vertexPosition.xyz;
}
