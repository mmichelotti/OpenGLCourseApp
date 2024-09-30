#include "DirectionalLight.h"
DirectionalLight::DirectionalLight() : light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(Light light, glm::vec3 direction)
	: light(light), direction(direction) {}

void DirectionalLight::Use(GLuint colorLocation, GLuint directionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation)
{
	light.Use(colorLocation, dIntensityLocation, aIntensityLocation);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}