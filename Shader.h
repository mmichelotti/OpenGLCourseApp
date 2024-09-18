#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFile(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	void Use();
	void Clear();

	GLuint GetProjectionLocation() { return uniformProjection; }
	GLuint GetModelLocation() { return uniformModel; }
	GLuint GetViewLocation() { return uniformView; }

	~Shader();

private:
	GLuint shaderID;
	GLuint uniformProjection;
	GLuint uniformModel;
	GLuint uniformView;
	void Compile(const char* vertexCode, const char* fragmentCode);
	void Add(GLuint program, const char* code, GLenum shaderType);
};

