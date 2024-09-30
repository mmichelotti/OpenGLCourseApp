#pragma once
#include "Light.h"
class DirectionalLight
{
public:
	DirectionalLight();
	DirectionalLight(Light light, glm::vec3 direction);
	void Use(GLuint colorLocation, GLuint directionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation);
private:
	Light light;
	glm::vec3 direction;
};

