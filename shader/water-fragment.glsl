#version 330 core

uniform vec3	    lightPosition;
uniform vec3	    lightColor;
uniform sampler2D   reflectionTexture;

in vec3	color;
in vec3	normal;
in vec3	currentPosition;

out vec4	FragColor;

vec4	getLight()
{
	float	ambient = 0.1f;
  	
    vec3	norm = normalize(normal);
    vec3	lightDirection = normalize(-lightPosition);
    float	diffuse = max(dot(norm, lightDirection), 0.0);

    return vec4(color * lightColor * (ambient + diffuse), 0.5f);
}

void main()
{
    vec2    screenUV = gl_FragCoord.xy / textureSize(reflectionTexture, 0);
    screenUV.y = 1.0f - screenUV.y;
    vec4    reflectionColor = texture(reflectionTexture, screenUV);

	FragColor = mix(getLight(), reflectionColor, 0.5);
}
