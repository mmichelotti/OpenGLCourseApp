#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include "Color.h"
class Light
{
public:
	Light();
	Light(Color color, GLfloat dIntensity, GLfloat aIntensity);

protected:
	Color color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

