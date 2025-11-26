#version 330 core

layout (location = 0) in vec2	aPosition;
layout (location = 1) in vec2	aTextureUV;

out vec2	textureUV;


void	main()
{
	gl_Position = vec4(aPosition.x, aPosition.y, 0.0f, 1.0f);
	textureUV = aTextureUV;
}
