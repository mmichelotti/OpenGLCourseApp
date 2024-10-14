#include "Light.h"


Light::Light()
{
	color = Color::White;

	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(GLfloat shadowWidth, GLfloat shadowHeight, Color color, GLfloat dIntensity, GLfloat aIntensity)
{
	shadowMap = new ShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
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

