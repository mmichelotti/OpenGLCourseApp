#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include "Color.h"
class Light
{
public:
	Light();
	Light(Color color, GLfloat dIntensity, GLfloat aIntensity);
	void Use(GLuint colorLocation, GLuint dIntensityLocation, GLuint aIntensityLocation);

	Color color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

