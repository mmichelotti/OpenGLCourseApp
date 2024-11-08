#pragma once
#include <stdio.h>
#include <GL/glew.h>
class ShadowMap
{
public:
	ShadowMap();
	ShadowMap(GLuint width, GLuint height);
	void Write();
	virtual bool Init();
	virtual void Read(GLenum textureUnit);
	GLuint GetShadowWidth() { return shadowWidth; }
	GLuint GetShadowHeight() { return shadowHeight; }
	~ShadowMap();

protected:
	GLuint FBO, shadowMap;
	GLuint shadowWidth, shadowHeight;
};

