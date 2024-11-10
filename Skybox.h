#pragma once
#include <vector>
#include <string>
#include <GL\glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "Global.h"
class Skybox
{
public:
	Skybox();
	Skybox(std::vector<std::string> faceLocation);
	void Draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
private:
	Mesh* mesh;
	Shader* shader;
	GLuint textureID;

	GLuint uniformProjection;
	GLuint uniformView;
};

