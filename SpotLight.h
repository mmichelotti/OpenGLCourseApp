#pragma once
#include "PointLight.h"
class SpotLight : PointLight
{
public:
	SpotLight();
	SpotLight(Light light, glm::vec3 position, Quadratic attenuation, glm::vec3 direction, GLfloat edge);
	void Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation, GLuint direcitonLocation, GLuint edgeLocation);
	void SetFlash(glm::vec3 position, glm::vec3 direction);
private:
	glm::vec3 direction;
	GLfloat edge, procEdge;
};

