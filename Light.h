#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
class Light
{
public:
	Light();
	Light(glm::vec3 color, glm::vec3 direction, GLfloat dIntensity, GLfloat aIntensity);
	void Use(GLuint colorLocation, GLuint directionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation);

private:
	glm::vec3 color;
	glm::vec3 direction;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

