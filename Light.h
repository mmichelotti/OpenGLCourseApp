#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
class Light
{
public:
	Light();
	Light(glm::vec3 color, GLfloat aIntensity);
	void Use(GLfloat aIntensityLocation, GLfloat aColorLocation);

private:
	glm::vec3 color;
	GLfloat ambientIntensity;
};

