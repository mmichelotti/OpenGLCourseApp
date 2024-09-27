#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "CommonValues.h"

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
	GLuint GetLightDirectionLocation() { return uniformDirectionalLight.direction; }
	GLuint GetSpecularLocation() { return uniformSpecular; }
	GLuint GetRoughnessLocation() { return uniformRoughness; }


	void SetDirectionalLight(DirectionalLight* dirLight);
	//move lights in separate struct or using vectors to not pass the count around
	void SetPointLights(PointLight* pointLights, unsigned int lightCount);



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

	//TODO base struct containing color, ambient, diffuse
	struct
	{
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;

		GLuint direction;
	} uniformDirectionalLight;

	GLuint uniformPointLightCount;

	struct
	{
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;

		GLuint position;

		GLuint constant;
		GLuint linear;
		GLuint exponent;

	} uniformPointLight[MAX_POINT_LIGHTS];

	void Compile(const char* vertexCode, const char* fragmentCode);
	void Add(GLuint program, const char* code, GLenum shaderType);
};

