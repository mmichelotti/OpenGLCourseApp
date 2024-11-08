#include "DirectionalLight.h"
#include "GLM/gtc/matrix_transform.hpp"

DirectionalLight::DirectionalLight() : light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	this->light.projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 20.0f);
}

DirectionalLight::DirectionalLight(Light light, GLfloat shadowResolution, glm::vec3 direction)
	: light(light), direction(direction) 
{	
	this->light.projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
	shadowMap = new ShadowMap();
	shadowMap->Init(shadowResolution, shadowResolution);
}

void DirectionalLight::Use(GLuint colorLocation, GLuint directionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation)
{
	light.Use(colorLocation, dIntensityLocation, aIntensityLocation);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}

glm::mat4 DirectionalLight::CalculateLightTransform()
{
	return light.projection * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
