#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include "DirectionalLight.h"
#include "PointLight.h"
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
	GLuint GetEyePositionLocation() { return uniformEyePosition; }
	GLuint GetAmbientColorLocation() { return uniformDirectionalLight.color; }
	GLuint GetAmbientIntensityLocation() { return uniformDirectionalLight.ambientIntensity; }
	GLuint GetDiffuseIntensityLocation() { return uniformDirectionalLight.diffuseIntensity; }
	GLuint GetLightDirectionLocation() { return uniformDirectionalLight.lightDirection; }
	GLuint GetSpecularLocation() { return uniformSpecular; }
	GLuint GetRoughnessLocation() { return uniformRoughness; }



	~Shader();

private:
	int pointLightCount;

	GLuint shaderID;
	GLuint uniformProjection;
	GLuint uniformModel;
	GLuint uniformView;
	GLuint uniformEyePosition;


	GLuint uniformSpecular;
	GLuint uniformRoughness;


	struct
	{
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;
		GLuint lightDirection;
	} uniformDirectionalLight;
	struct
	{

	} uniformPointLight;

	void Compile(const char* vertexCode, const char* fragmentCode);
	void Add(GLuint program, const char* code, GLenum shaderType);
};

