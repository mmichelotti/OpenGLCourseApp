#version 330		

// Taking input from the .vert									
in vec4 vCol;	
in vec2 TexCoord;

// the actual out of the pixel color
out vec4 color;	

// uniform texture passed from cpp
uniform sampler2D theTexture;

void main()			
{	
	//texture() glsl method to sample a texture
    vec4 texture = texture(theTexture, TexCoord);
	color = texture * vCol;
}