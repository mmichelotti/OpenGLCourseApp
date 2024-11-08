#pragma once
#include "Light.h"
class DirectionalLight
{
public:
	DirectionalLight();
	DirectionalLight(Light light, GLfloat shadowResolution, glm::vec3 direction);
	void Use(GLuint colorLocation, GLuint directionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation);
	glm::mat4 CalculateLightTransform();

	ShadowMap* GetShadowMap() { return shadowMap; }
	ShadowMap* shadowMap;
private:
	Light light;
	glm::vec3 direction;
};

