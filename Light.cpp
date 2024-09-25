#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	direction = glm::vec3(0.0f, -1.0f, 0.0f);

	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(glm::vec3 color, glm::vec3 direction, GLfloat dIntensity, GLfloat aIntensity)
{
	this->color = color;
	this->direction = direction;
	this->ambientIntensity = aIntensity;
	this->diffuseIntensity = dIntensity;
}

void Light::Use(GLuint colorLocation, GLuint directionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation)
{
	//Bind the color from the .shader to the cpp information
	glUniform3f(colorLocation, color.x, color.y, color.z);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(aIntensityLocation, ambientIntensity);
	glUniform1f(dIntensityLocation, diffuseIntensity);
}
