#pragma once
#include "Light.h"
#include "Quadratic.h"
class PointLight
{
public:
	PointLight();
	PointLight(Light light, glm::vec3 position, Quadratic<GLfloat> attenuation);
	void Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation);
protected:
	Light light;
	glm::vec3 position;
	Quadratic<GLfloat> attenuation;
};

