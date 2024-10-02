#include "SpotLight.h"

SpotLight::SpotLight() : PointLight(), direction(glm::vec3(0.0f, -1.0f, 0.0f)), edge(0.0f) 
{
	procEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(Light light, glm::vec3 position, Quadratic attenuation, glm::vec3 direction, GLfloat edge) 
	: PointLight(light, position, attenuation), edge(edge)
{
	 
	this->direction = glm::normalize(direction);
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation, GLuint direcitonLocation, GLuint edgeLocation)
{
	light.Use(colorLocation, dIntensityLocation, aIntensityLocation);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constLocation, attenuation.constant);
	glUniform1f(linLocation, attenuation.linear);
	glUniform1f(expLocation, attenuation.exponent);

	glUniform3f(direcitonLocation, direction.x, direction.y, direction.z);
	glUniform1f(edgeLocation,procEdge);

}

void SpotLight::SetFlash(glm::vec3 position, glm::vec3 direction)
{
	this->position = position;
	this->direction = direction;
}
