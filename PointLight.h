#pragma once
#include "Light.h"
struct Quadratic
{
	// Attenuation obtained by Color / by quadratic equation (ax^2 + bx + c)
	GLfloat constant; 
	GLfloat linear;   
	GLfloat exponent; 

	Quadratic() : 
		constant(1.0f), linear(0.0f), exponent(0.0f) {}
	Quadratic(GLfloat constant, GLfloat linear, GLfloat exponent) :
		constant(constant), linear(linear), exponent(exponent) {}
};
class PointLight
{
public:
	PointLight();
	PointLight(Light light, glm::vec3 position, Quadratic attenuation);
	void Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation);
protected:
	Light light;
	glm::vec3 position;
	Quadratic attenuation;
};

