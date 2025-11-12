#version 330 core

uniform sampler2D	diffuse0;
uniform sampler2D	specular0;
uniform vec3		camPos;

in vec3	currentPos;
in vec3	color;
in vec3	normal;
in vec2	texUV;

out vec4	FragColor;


void main()
{
	FragColor = vec4(color, 1.0f);
}
