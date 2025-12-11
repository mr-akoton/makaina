#version 330 core

const float  LIGHT_AMBIENT = 0.1f; 

uniform vec3	    lightPosition;
uniform vec3	    lightColor;
uniform sampler2D   reflectionTexture;
uniform sampler2D   refractionTexture;
uniform sampler2D   depthTexture;

in vec3	color;
in vec3	normal;
in vec3 toCameraVector;

out vec4	FragColor;

/* ========================================================================== */
/*                                    UTILS                                   */
/* ========================================================================== */

float   toLinearDepth(float depth)
{
    float   near = 0.1f;
    float   far = 1000.0f;

    return 2.0f * near * far / (far + near - (2.0f * depth - 1.0f) * (far - near));
}

float   getWaterDepth(vec2 textureUV)
{
    float   depth = texture(depthTexture, textureUV).r;
    float   floorDistance = toLinearDepth(depth);
    depth = gl_FragCoord.z;
    float   waterDistance = toLinearDepth(depth);
    return floorDistance - waterDistance;
}

vec3    getMurkiness(vec3 refractionColor, float waterDepth)
{
    float murkyFactor = smoothstep(0, 15, waterDepth);
    float murkiness = 0.4 + murkyFactor * (0.75 - 0.4);
    return mix(refractionColor, color, murkiness);
}

float   getFresnel()
{
    vec3   viewVector = normalize(toCameraVector);
    vec3   norm = normalize(normal); 
    float   refractiveFactor = dot(viewVector, norm);
    return clamp(pow(refractiveFactor, 0.9f), 0.0f, 1.0f);
}

/* ========================================================================== */
/*                               LIGHT AND COLOR                              */
/* ========================================================================== */

vec3    getColor(vec2 textureUV, float waterDepth)
{
    vec3    refractionColor = texture(refractionTexture, textureUV).rgb;
    refractionColor = getMurkiness(refractionColor, waterDepth);
    vec3    reflectionColor = texture(reflectionTexture, vec2(textureUV.x, 1.0f - textureUV.y)).rgb;

    return mix(reflectionColor, refractionColor, getFresnel());
}

vec4    getLight(vec2 textureUV, float waterDepth)
{
    vec3    norm = normalize(normal);
    vec3    lightDirection = normalize(-lightPosition);
    float   diffuse = max(dot(norm, lightDirection), 0.0f);

    return vec4(getColor(textureUV, waterDepth) * lightColor * (LIGHT_AMBIENT + diffuse), 1.0f);
}

/* ========================================================================== */
/*                                    MAIN                                    */
/* ========================================================================== */

void    main()
{
    vec2    screenUV = gl_FragCoord.xy / textureSize(reflectionTexture, 0);
    float   waterDepth = getWaterDepth(screenUV);

    FragColor = getLight(screenUV, waterDepth);
    FragColor.a = clamp(waterDepth / 1.0f, 0.0f, 1.0f);
}
