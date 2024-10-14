#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include "Color.h"
#include "ShadowMap.h"
class Light
{
public:
	Light();
	Light(GLfloat shadowWidth, GLfloat shadowHeight, Color color, GLfloat dIntensity, GLfloat aIntensity);
	void Use(GLuint colorLocation, GLuint dIntensityLocation, GLuint aIntensityLocation);
	ShadowMap* GetShadowMap() { return shadowMap; }
	Color color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

	glm::mat4 projection;
	ShadowMap* shadowMap;
};

