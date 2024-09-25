#pragma once
#include <GL/glew.h>
class Material
{
public:
	Material();
	Material(GLfloat specular, GLfloat roughness);
	void Use(GLuint specularLocation, GLuint roughnessLocation);
private:
	GLfloat specular = 0.5f;
	GLfloat roughness = 0.5f;
};

