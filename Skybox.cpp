#include "Skybox.h"
#include "Vec2.h"
Skybox::Skybox() {}

Skybox::Skybox(std::vector<std::string> faceLocation)
{
	shader = new Shader();
	shader->CreateFromFile("Shaders/Skybox.vert", "Shaders/Skybox.frag");
	uniformProjection = shader->GetProjectionLocation();
	uniformView = shader->GetViewLocation();

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	Vec2<int> size = Vec2<int>();
	int bitDepth;
	for (size_t i = 0; i < 6; i++)
	{
		unsigned char* texData = stbi_load(faceLocation[i].c_str(), &size.x, &size.y, &bitDepth, 0);
		if (!texData)
		{
			printf("Failed to find %s\n", faceLocation[i].c_str());
			return;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		stbi_image_free(texData);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //texture repeat along x axis
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //texture repeat along y axis
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //blend pixel together, GL_NEAREST keep pixelated
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //texture repeat along x axis

	// Mesh Setup


	mesh = new Mesh(CUBE);

}

void Skybox::Draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));

	glDepthMask(GL_FALSE);
	shader->Use();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	shader->Validate();
	mesh->Render();

	glDepthMask(GL_TRUE);
}
