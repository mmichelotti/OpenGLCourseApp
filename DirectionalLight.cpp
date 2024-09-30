#include "DirectionalLight.h"
DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(Color color, glm::vec3 direction, GLfloat dIntensity, GLfloat aIntensity)
	: Light(color,dIntensity, aIntensity)
{
	this->direction = direction;
}

void DirectionalLight::Use(GLuint colorLocation, GLuint directionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation)
{
	Light::Use(colorLocation, dIntensityLocation, aIntensityLocation);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}