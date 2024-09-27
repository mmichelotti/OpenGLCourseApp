#version 330		

const int MAX_POINT_LIGHTS = 3;
// Taking input from the .vert	
// Preparing out to read from the cpp
in vec4 VertexColor;	
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
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
struct Material
{
    float specular;
    float roughness;
};

// uniform texture passed from cpp
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightCount;

uniform sampler2D theTexture;
uniform Material material;
uniform vec3 eyePosition;


vec4 CalculateLightByDirection(Light light, vec3 direction)
{
    vec3 ambientColor = light.color * light.ambientIntensity;
    float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
    // A.B = |A||B| * cos(angle)
    // The length of A and B is normalized so
    // A.B = cos(angle)
    // So the dot is giving the cos(angle)
    // Since when it reaches 0 is already at maximum "darkness" we clamp so it doesnt go up to -1
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
    return vec4(ambientColor + diffuseColor + specularColor, 1.0f);
}
vec4 GetDirectionalLight(){return CalculateLightByDirection(directionalLight.base, directionalLight.direction);}
void main()			
{	
    //texture() glsl method to sample a texture
    vec4 texture = texture(theTexture, TexCoord);
    Color = texture * GetDirectionalLight();
}