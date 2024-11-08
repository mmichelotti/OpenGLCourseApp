#pragma once
#include "Light.h"
#include "Quadratic.h"
#include <vector>
#include "OmniShadowMap.h"
class PointLight
{
public:
	PointLight();
	PointLight(Light light, GLuint shadowResolution, GLfloat far, glm::vec3 position, Quadratic<GLfloat> attenuation);
	void Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation);
	std::vector<glm::mat4> CalculateLightTransform();
	GLfloat GetFarPlane() { return farPlane; }
	glm::vec3 GetPosition() { return position; }
	ShadowMap* GetShadowMap() { return shadowMap; }
protected:
	ShadowMap* shadowMap;
	Light light;
	GLfloat farPlane;
	glm::vec3 position;
	Quadratic<GLfloat> attenuation;
};

