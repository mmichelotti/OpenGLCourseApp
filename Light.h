#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
class Light
{
public:
	Light();
	Light(glm::vec3 color, GLfloat dIntensity, GLfloat aIntensity);

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

