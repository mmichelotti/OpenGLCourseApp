#pragma once
#include "Light.h"
class PointLight : Light
{
	PointLight();
	PointLight(glm::vec3 color, GLfloat dIntensity, GLfloat aIntensity, glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat exponent);
	void Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation);
private:
	glm::vec3 position;
	// Attenuation obtained by Color / by quadratic equation (ax^2 + bx + c)
	GLfloat constant;
	GLfloat linear;
	GLfloat exponent;
};

