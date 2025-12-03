#version 330 core

uniform vec3	lightPosition;
uniform vec3	lightColor;

in vec3	color;
in vec3 normal;
in vec3	currentPosition;

out vec4	FragColor;


vec4	getLight()
{
	float	ambient = 0.1f;
  	
    vec3	norm = normalize(normal);
    vec3	lightDirection = normalize(-lightPosition);
    float	diffuse = max(dot(norm, lightDirection), 0.0);

    return vec4(color * lightColor * (ambient + diffuse), 1.0f);
}

void main()
{
	FragColor = getLight();
}
