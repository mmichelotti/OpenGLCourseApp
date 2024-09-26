#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);

	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(glm::vec3 color, GLfloat dIntensity, GLfloat aIntensity)
{
	this->color = color;
	this->ambientIntensity = aIntensity;
	this->diffuseIntensity = dIntensity;
}
