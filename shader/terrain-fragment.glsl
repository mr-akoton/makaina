#version 330 core

uniform vec3		lightPosition;
uniform vec3		lightColor;
uniform vec3		cameraPosition;
uniform float		cameraNear;
uniform float		cameraFar;
uniform float		heightFactor;
uniform sampler2D	diffuse0;
uniform sampler2D	specular0;

uniform vec3		color0;
uniform vec3		color1;
uniform vec3		color2;

in float	height;
in vec3		normal;
in vec3		color;
in vec2		textureUV;

out vec4	FragColor;


vec3	getColorByHeight()
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

vec4	directionLight()
{
	float	ambienLight = 0.2f;

	vec3	norm = normalize(normal);
	vec3	lightDirection = normalize(lightPosition);
	float	diffuse = max(dot(norm, lightDirection), 0.0f);

	return vec4(getColorByHeight() * lightColor, 1.0f) * (diffuse + ambienLight);
}

float	linearizeDepth(float depth)
{
	return (
		2.0f * cameraNear * cameraFar)
		/ (cameraFar + cameraNear - (depth * 2.0f - 1.0f)
		* (cameraFar - cameraNear)
	);
}

float	logisticDepth(float depth, float steepness, float offset)
{
	float	zVal = linearizeDepth(depth);
	return 1 / (1 + exp(-steepness * (zVal - offset)));
}

void main()
{
	float	depth = logisticDepth(gl_FragCoord.z, 0.1f, 250.0f);
	FragColor = directionLight() * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
}
