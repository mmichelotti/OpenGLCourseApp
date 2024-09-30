#include "PointLight.h"
PointLight::PointLight() : Light()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
}
PointLight::PointLight(Color color, glm::vec3 position, GLfloat dIntensity, GLfloat aIntensity,  GLfloat constant, GLfloat linear, GLfloat exponent)
	: Light(color, dIntensity, aIntensity)
{
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->exponent = exponent;
}
void PointLight::Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation)
{
	Light::Use(colorLocation, dIntensityLocation, aIntensityLocation);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constLocation, constant);
	glUniform1f(linLocation, linear);
	glUniform1f(expLocation, exponent);
}