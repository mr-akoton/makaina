#version 330 core

const float AMBIEN_LIGHT = 0.1f;
const float SPECULAR_STRENGTH = 0.5f;

uniform vec3	u_viewPosition;	
uniform vec3	u_lightPosition;
uniform vec3	u_lightColor;

in vec3 pass_color;
in vec3 pass_normal;

out vec4	FragColor;

/* ========================================================================== */
/*                                    LIGHT                                   */
/* ========================================================================== */

vec4	getLight()
{
    vec3	normal = normalize(pass_normal);
    vec3	lightDirection = normalize(-u_lightPosition);
    float	diffuse = max(dot(normal, lightDirection), 0.0);

    return vec4(pass_color * u_lightColor * (AMBIEN_LIGHT + diffuse), 1.0f);
}

/* ========================================================================== */
/*                                    MAIN                                    */
/* ========================================================================== */

void main()
{
	FragColor = getLight();
}
