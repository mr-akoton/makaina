#version 330 core

const float AMBIEN_LIGHT = 0.1f;
const float SPECULAR_STRENGTH = 0.5f;

uniform vec3	u_viewPosition;	
uniform vec3	u_lightPosition;
uniform vec3	u_lightColor;

in vec3	pass_color;
in vec3 pass_normal;
in vec3 pass_vertexPosition;

out vec4	FragColor;

/* ========================================================================== */
/*                                   NORMAL                                   */
/* ========================================================================== */

vec3    getNormal()
{
    vec3    dx = dFdx(pass_vertexPosition);
    vec3    dy = dFdy(pass_vertexPosition);
    return normalize(cross(dx, dy));
}

/* ========================================================================== */
/*                                    LIGHT                                   */
/* ========================================================================== */

vec4	getLight()
{
    vec3	normal = getNormal();
    vec3	lightDirection = normalize(-u_lightPosition);
    float	diffuse = max(dot(normal, lightDirection), 0.0f);

    vec3   viewDirection = normalize(u_viewPosition - pass_vertexPosition);
    vec3   reflectionDirection = reflect(-lightDirection, normal);
    float  specularValue = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
    vec3   specular = SPECULAR_STRENGTH * specularValue * u_lightColor;

    vec3    result = (AMBIEN_LIGHT + diffuse + specular) * pass_color;

    return vec4(result, 1.0f);
}

/* ========================================================================== */
/*                                    MAIN                                    */
/* ========================================================================== */

void main()
{
	FragColor = getLight();
}
