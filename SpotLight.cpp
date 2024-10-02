#include "SpotLight.h"

SpotLight::SpotLight() : PointLight(), direction(glm::vec3(0.0f, -1.0f, 0.0f)), radius(0.0f) 
{
	processedRadius = cosf(glm::radians(radius));
}

SpotLight::SpotLight(Light light, glm::vec3 position, Quadratic<GLfloat> attenuation, glm::vec3 direction, GLfloat radius)
	: PointLight(light, position, attenuation), radius(radius)
{
	this->direction = glm::normalize(direction);
	processedRadius = cosf(glm::radians(radius));
}

void SpotLight::Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation, GLuint direcitonLocation, GLuint radiusLocation)
{
	light.Use(colorLocation, dIntensityLocation, aIntensityLocation);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constLocation, attenuation.constant);
	glUniform1f(linLocation, attenuation.linear);
	glUniform1f(expLocation, attenuation.exponent);

	glUniform3f(direcitonLocation, direction.x, direction.y, direction.z);
	glUniform1f(radiusLocation, processedRadius);

}

void SpotLight::SetPositionAndDirection(glm::vec3 position, glm::vec3 direction)
{
	this->position = position;
	this->direction = direction;
}
