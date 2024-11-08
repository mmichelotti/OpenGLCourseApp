#include "PointLight.h"
#include "GLM/gtc/matrix_transform.hpp"
PointLight::PointLight() : 
	light(), position(glm::vec3(0.0f, 0.0f, 0.0f)), attenuation() {}


PointLight::PointLight(Light light, GLuint shadowResolution, GLfloat farPlane, glm::vec3 position, Quadratic<GLfloat> attenuation)
	: light(light), farPlane(farPlane), position(position), attenuation(attenuation) 
{
	this->light.projection = glm::perspective(glm::radians(90.0f),1.0f, 0.0f, farPlane);
	shadowMap = new OmniShadowMap(shadowResolution, shadowResolution);
	shadowMap->Init();
}

void PointLight::Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation)
{
	light.Use(colorLocation, dIntensityLocation, aIntensityLocation);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constLocation, attenuation.constant);
	glUniform1f(linLocation, attenuation.linear);
	glUniform1f(expLocation, attenuation.exponent);
}

std::vector<glm::mat4> PointLight::CalculateLightTransform()
{
	std::vector<glm::mat4> lightMatrices;
	lightMatrices.push_back(light.projection * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f , 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	lightMatrices.push_back(light.projection * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	lightMatrices.push_back(light.projection * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	lightMatrices.push_back(light.projection * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));

	lightMatrices.push_back(light.projection * glm::lookAt(position, position + glm::vec3(0, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	lightMatrices.push_back(light.projection * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	return lightMatrices;
}
