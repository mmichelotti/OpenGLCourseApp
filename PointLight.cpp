#include "PointLight.h"
PointLight::PointLight() : 
	light(), position(glm::vec3(0.0f, 0.0f, 0.0f)), attenuation() {}

PointLight::PointLight(Light light, glm::vec3 position, Quadratic attenuation)
	: light(light), position(position), attenuation(attenuation) {}

void PointLight::Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation)
{
	light.Use(colorLocation, dIntensityLocation, aIntensityLocation);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constLocation, attenuation.constant);
	glUniform1f(linLocation, attenuation.linear);
	glUniform1f(expLocation, attenuation.exponent);
}