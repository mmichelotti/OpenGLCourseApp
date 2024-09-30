#pragma once
#include "Light.h"
class PointLight
{
public:
	PointLight();
	PointLight(Light light, glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat exponent);
	void Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation);
	
	Light light;
	glm::vec3 position;
	// Attenuation obtained by Color / by quadratic equation (ax^2 + bx + c)
	GLfloat constant;
	GLfloat linear;
	GLfloat exponent;
};

