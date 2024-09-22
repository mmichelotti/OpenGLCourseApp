#version 330		

// Taking input from the .vert	
// Preparing out to read from the cpp
in vec4 vCol;	
in vec2 TexCoord;
out vec4 color;	

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;
};
// uniform texture passed from cpp
uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;


void main()			
{	
    //texture() glsl method to sample a texture
    vec4 texture = texture(theTexture, TexCoord);
    vec3 ambientColor = directionalLight.color * directionalLight.ambientIntensity;
    color = texture * vec4(ambientColor, 1.0f);
}