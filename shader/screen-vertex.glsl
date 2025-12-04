#version 330 core

layout (location = 0) in vec2	l_position;
layout (location = 1) in vec2	l_textureUV;

out vec2	textureUV;


void main()
{
    gl_Position = vec4(l_position.x, l_position.y, 0.0, 1.0); 
    textureUV = l_textureUV;
}
