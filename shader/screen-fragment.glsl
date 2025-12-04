#version 330 core

uniform sampler2D screenTexture;
  
in vec2	textureUV;

out vec4	FragColor;


void main()
{
	FragColor = vec4(vec3(1.0f - texture(screenTexture, textureUV)), 1.0f);
}
