#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
}

Light::Light(glm::vec3 color, GLfloat aIntensity)
{
	this->color = color;
	this->ambientIntensity = aIntensity;
}

void Light::Use(GLfloat aIntensityLocation, GLfloat aColorLocation)
{
	//bind the ambient color location to our rgb color to that uniform variable
	//same for ambient intensity
	glUniform3f(aColorLocation, color.x, color.y, color.z);
	glUniform1f(aIntensityLocation, ambientIntensity);
}
