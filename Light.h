#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
class Light
{
public:
	Light();
	Light(glm::vec3 color, glm::vec3 direction, GLfloat aIntensity, GLfloat dIntensity);
	void Use(GLfloat colorLocation, GLfloat directionLocation, GLfloat aIntensityLocation, GLfloat dIntensityLocation);

private:
	glm::vec3 color;
	glm::vec3 direction;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

