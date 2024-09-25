#version 330		

// Taking input from the .vert	
// Preparing out to read from the cpp
in vec4 VertexColor;	
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 Color;	

// Usually ambient is given by GI but for semplicity im sticking with the classic hard coded
struct DirectionalLight
{
    vec3 color;
    vec3 direction;
    float ambientIntensity;
    float diffuseIntensity;
};
struct Material
{
    float specular;
    float roughness;
};

// uniform texture passed from cpp
uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 eyePosition;
void main()			
{	
    //texture() glsl method to sample a texture
    vec4 texture = texture(theTexture, TexCoord);
    vec3 ambientColor = directionalLight.color * directionalLight.ambientIntensity;
    float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
    // A.B = |A||B| * cos(angle)
    // The length of A and B is normalized so
    // A.B = cos(angle)
    // So the dot is giving the cos(angle)
    // Since when it reaches 0 is already at maximum "darkness" we clamp so it doesnt go up to -1
    vec3 diffuseColor = directionalLight.color * directionalLight.diffuseIntensity * diffuseFactor;
    
    vec3 specularColor = vec3(0.0f,0.0f,0.0f);
    //refactor if with max
    if(diffuseFactor > 0.0f)
    {
        //Direction from pixel to view 
        //Should be the PixelNormalWS
        vec3 fragToView = normalize(eyePosition - FragPos);
        vec3 reflectedVertex = normalize(reflect(directionalLight.direction, normalize(Normal)));
        float specularFactor = dot(fragToView, reflectedVertex);
        if(specularFactor > 0.0f)
        {
            specularFactor = pow(specularFactor, material.roughness);
            specularColor = directionalLight.color * material.specular * specularFactor;
        }
    }
    
    Color = vec4(ambientColor + diffuseColor + specularColor, 1.0f) * texture;
}