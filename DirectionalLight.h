#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(Color color, glm::vec3 direction, GLfloat dIntensity, GLfloat aIntensity);
	void Use(GLuint colorLocation, GLuint directionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation);
private:
	glm::vec3 direction;
};

