#include "Light.h"

Light::Light()
{
	color = Color::White;

	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(Color color, GLfloat dIntensity, GLfloat aIntensity)
{
	this->color = color;
	this->ambientIntensity = aIntensity;
	this->diffuseIntensity = dIntensity;
}

void Light::Use(GLuint colorLocation, GLuint dIntensityLocation, GLuint aIntensityLocation)
{
	glUniform3f(colorLocation, color.r, color.g, color.b);
	glUniform1f(aIntensityLocation, ambientIntensity);
	glUniform1f(dIntensityLocation, diffuseIntensity);
}

