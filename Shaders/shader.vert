#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 norm;

out vec4 VertexColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
															
uniform mat4 model;											
uniform mat4 projection;
uniform mat4 view;
															
void main()													
{	
	vec4 modelPos = model * vec4(pos, 1.0f);														
	gl_Position = projection * view * modelPos;	
	FragPos = modelPos.xyz;
    VertexColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	TexCoord = texCoord;
    Normal = mat3(transpose(inverse(model))) * norm;
	// use the model to get any change in rotation and scaling
	// inverse transpose to account for non uniform scaling (example scaling only the x on an object and keep their normals correct)
	// cast to mat3() because we dont need the 4th column and row for a rgb normal
	
}													