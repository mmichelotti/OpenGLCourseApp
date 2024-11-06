#version 330		

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

// Taking input from the .vert	
// Preparing out to read from the cpp
in vec4 VertexColor;	
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 DirectionalLightSpacePos;
out vec4 Color;	

struct Light
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
};
// Usually ambient is given by GI but for semplicity im sticking with the classic hard coded
struct DirectionalLight
{
    Light base;
    vec3 direction;
};
struct PointLight
{
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};
struct SpotLight
{
    PointLight base;
    vec3 direction;
    float edge;
};
struct Material
{
    float specular;
    float roughness;
};

// uniform texture passed from cpp
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int pointLightCount;
uniform int spotLightCount;
uniform sampler2D theTexture;
uniform sampler2D directionalShadowMap;
uniform Material material;
uniform vec3 eyePosition;

float CalculateDirectionalShadowFactor(DirectionalLight light)
{
    vec3 projCoords = DirectionalLightSpacePos.xyz / DirectionalLightSpacePos.w;
    projCoords = (projCoords * 0.5f) + 0.5f;
    float current = projCoords.z;

    //bias to resolve shadow acne
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(light.direction);
    float bias = max(0.05f * (1- dot(normal,lightDir)), 0.005f);

    vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);
    float shadow = 0.0f;
    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x,y) * texelSize).r;
            shadow += current - bias > pcfDepth ? 1.0f : 0.0f;
        }
    }
    shadow /= 9.0f;
    if(projCoords.z > 1.0f)
    {
        shadow = 0.0f;
    }
    return shadow;
}


vec4 CalculateLightByDirection(Light light, vec3 direction, float shadowFactor)
{
    // A.B = |A||B| * cos(angle)
    // The length of A and B is normalized so
    // A.B = cos(angle)
    // So the dot is giving the cos(angle)
    // Since when it reaches 0 is already at maximum "darkness" we clamp so it doesnt go up to -1
    vec3 ambientColor = light.color * light.ambientIntensity;
    float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
    vec3 diffuseColor = light.color * light.diffuseIntensity * diffuseFactor;
    
    vec3 specularColor = vec3(0.0f,0.0f,0.0f);
    //refactor if with max
    if(diffuseFactor > 0.0f)
    {
        //Direction from pixel to view 
        //Should be the PixelNormalWS
        vec3 fragToView = normalize(eyePosition - FragPos);
        vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
        float specularFactor = dot(fragToView, reflectedVertex);
        if(specularFactor > 0.0f)
        {
            specularFactor = pow(specularFactor, material.roughness);
            specularColor = light.color * material.specular * specularFactor;
        }
    }
    return vec4(ambientColor + (1.0f - shadowFactor) * (diffuseColor + specularColor), 1.0f);
}
vec4 CalculatePointLight(PointLight pLight)
{
        //ax^2 + bx + c
        vec3 difference = FragPos - pLight.position;
        vec3 direction = normalize(difference);
        float a = pLight.exponent;
        float x = length(difference);
        float b = pLight.linear;
        float c = pLight.constant;
        float attenuation = (a*x*x) + (b*x) + (c);

        vec4 lightColor = CalculateLightByDirection(pLight.base, direction, 0.0f);
        return (lightColor/attenuation);
}
vec4 CalculateSpotLight(SpotLight sLight)
{
    vec3 rayDirection = normalize(FragPos - sLight.base.position);
    float sLightFactor = dot(rayDirection, sLight.direction);
    if(sLightFactor > sLight.edge)
    {
        vec4 color = CalculatePointLight(sLight.base);
        //resize light factor and edge in 01 range
        return color * (1.0f - ((1.0f - sLightFactor) * (1.0f/(1.0f - sLight.edge))));
    }
    else
    {
        return vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
}
vec4 PointLightsColor()
{
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    for(int i = 0; i < pointLightCount; i++)
    {
        color += CalculatePointLight(pointLights[i]);
    };
    return color;
};
vec4 SpotLightsColor()
{
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    for(int i = 0; i < spotLightCount; i++)
    {
        color += CalculateSpotLight(spotLights[i]);
    };
    return color;
}
vec4 DirectionalLightColor()
{
    float shadowFactor = CalculateDirectionalShadowFactor(directionalLight);
    return CalculateLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);  
}
void main()			
{	
    //texture() glsl method to sample a texture
    vec4 texture = texture(theTexture, TexCoord);
    vec4 sceneLightsColor = DirectionalLightColor() + PointLightsColor() + SpotLightsColor();
    Color = texture * sceneLightsColor;
}