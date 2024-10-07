#pragma once

#include <GL\glew.h>
#include "stb_image.h"
#include "Vec2.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLocation);


	void Initialize();

	bool LoadRGBA();
	bool LoadRGB();
	void Use();
	void Clear();

	~Texture();
private:
	GLuint ID;
	Vec2<int> size;
	int bitDepth;
	const char* fileLocation;
};

