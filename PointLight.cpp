#include "PointLight.h"
PointLight::PointLight() : 
	light(), position(glm::vec3(0.0f, 0.0f, 0.0f)), constant(1.0f), linear(0.0f), exponent(0.0f) {}

PointLight::PointLight(Light light, glm::vec3 position,  GLfloat constant, GLfloat linear, GLfloat exponent)
	: light(light), position(position), constant(constant), linear(linear), exponent(exponent) {}

void PointLight::Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation)
{
	light.Use(colorLocation, dIntensityLocation, aIntensityLocation);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constLocation, constant);
	glUniform1f(linLocation, linear);
	glUniform1f(expLocation, exponent);
}