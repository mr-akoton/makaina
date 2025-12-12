#version 330 core

layout (location = 0) in vec3	l_position;
layout (location = 1) in vec3	l_normal;
layout (location = 2) in vec3	l_color;
layout (location = 3) in vec2	l_textureUV;

uniform mat4	u_model;
uniform mat4	u_projection;

out vec3	pass_color;
out vec3	pass_normal;
out vec3	pass_vertexPosition;

/* ========================================================================== */
/*                                    MAIN                                    */
/* ========================================================================== */

void	main()
{
	vec4	vertexPosition = u_model * vec4(l_position, 1.0f);

	gl_Position = u_projection * u_model * vertexPosition;
	pass_color = l_color;
	pass_normal = l_normal;
	pass_vertexPosition = pass_vertexPosition.xyz;
}
