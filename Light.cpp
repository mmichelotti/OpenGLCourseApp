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
