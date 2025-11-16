#version 330 core

layout (location = 0) in vec3	aPosition;
layout (location = 1) in vec3	aNormal;
layout (location = 2) in vec3	aColor;
layout (location = 3) in vec2	aTextureUV;

uniform mat4	model;
uniform mat4	cameraMatrix;

out vec3	currentPosition;
out vec3	normal;
out vec3	color;
out vec2	textureUV;


void main()
{
	currentPosition = vec3(model * vec4(aPosition, 1.0f));

	gl_Position = cameraMatrix * vec4(currentPosition, 1.0f);

	normal = aNormal;
	color = aColor;
	textureUV = aTextureUV;
}
