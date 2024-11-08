#pragma once
#include "ShadowMap.h"
class OmniShadowMap : public ShadowMap
{
public:
	OmniShadowMap(GLuint width, GLuint height);
	bool Init();
	void Read(GLenum textureUnit);
};

