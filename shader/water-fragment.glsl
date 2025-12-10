#version 330 core

const float  LIGHT_AMBIENT = 0.1f; 

uniform vec3	    lightPosition;
uniform vec3	    lightColor;
uniform sampler2D   reflectionTexture;

in vec3	color;
in vec3	normal;
in vec3	currentPosition;
in vec3 toCameraVector;

out vec4	FragColor;

float   getFresnel()
{
    vec3   viewVector = normalize(toCameraVector);
    vec3   norm = normalize(normal); 
    float   refractiveFactor = dot(viewVector, norm);
    return clamp(pow(refractiveFactor, 0.9f), 0.0f, 1.0f);
}

vec3    getColor()
{
    vec2    screenUV = gl_FragCoord.xy / textureSize(reflectionTexture, 0);
    screenUV.y = 1.0 - screenUV.y;

    vec3    reflectionColor = texture(reflectionTexture, screenUV).rgb;

    return mix(reflectionColor, color, getFresnel());
}

vec4    getLight()
{
    vec3    norm = normalize(normal);
    vec3    lightDirection = normalize(-lightPosition);
    float   diffuse = max(dot(norm, lightDirection), 0.0f);

    return vec4(getColor() * lightColor * (LIGHT_AMBIENT + diffuse), 0.8f);
}

void    main()
{
    FragColor = getLight();
}
