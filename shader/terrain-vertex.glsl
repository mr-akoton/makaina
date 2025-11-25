#version 330 core

layout (location = 0) in vec3	aPosition;
layout (location = 1) in vec3	aNormal;
layout (location = 2) in vec3	aColor;
layout (location = 3) in vec2	aTextureUV;

uniform mat4		model;
uniform mat4		cameraMatrix;
uniform float		heightFactor;
uniform sampler2D	heightMap;

uniform vec3		color0;
uniform vec3		color1;
uniform vec3		color2;

out	DATA
{
	vec3	normal;
	vec3	color;
	vec2	textureUV;
	mat4	projection;
}	data_out;


vec3	getColorByHeight(float height)
{
    if (height < 0.4f)
	{
        return color2;
    }
	else if (height < 0.7f)
	{
		float t = (height - 0.4f) / 0.3f;
		return mix(color2, color1, t);
	}
	else
	{
        float t = (height - 0.7f) / 0.3f;
	    return mix(color1, color0, t);
    }
}

void	main()
{
	float	noiseValue = texture(heightMap, aTextureUV).r;
	float	height = noiseValue * heightFactor;

	vec3	currentPosition = vec3(model * vec4(
		aPosition.x,
		height,
		aPosition.z, 1.0f
	));

	gl_Position = vec4(currentPosition, 1.0f);

	data_out.normal = aNormal;
	data_out.color = getColorByHeight(noiseValue);
	data_out.textureUV = aTextureUV;
	data_out.projection = cameraMatrix;
}
