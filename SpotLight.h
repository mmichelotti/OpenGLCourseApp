#pragma once
#include "PointLight.h"
class SpotLight : PointLight
{
public:
	SpotLight();
	SpotLight(Light light, glm::vec3 position, Quadratic<GLfloat> attenuation, glm::vec3 direction, GLfloat edge);
	void Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation, GLuint direcitonLocation, GLuint edgeLocation);
	void SetPositionAndDirection(glm::vec3 position, glm::vec3 direction);
private:
	glm::vec3 direction;

	GLfloat radius, processedRadius;
};

