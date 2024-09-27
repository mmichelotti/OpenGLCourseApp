#include "PointLight.h"
PointLight::PointLight() : Light()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
}
PointLight::PointLight(glm::vec3 color, GLfloat dIntensity, GLfloat aIntensity, glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat exponent)
	: Light(color, dIntensity, aIntensity)
{
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->exponent = exponent;
}
void PointLight::Use(GLuint colorLocation, GLuint positionLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint constLocation, GLuint linLocation, GLuint expLocation)
{
	//Bind the color from the .shader to the cpp information
	glUniform3f(colorLocation, color.x, color.y, color.z);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(aIntensityLocation, ambientIntensity);
	glUniform1f(dIntensityLocation, diffuseIntensity);
	glUniform1f(constLocation, constant);
	glUniform1f(linLocation, linear);
	glUniform1f(expLocation, exponent);
}