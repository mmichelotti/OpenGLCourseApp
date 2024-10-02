#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL\glew.h>
#include "LightInfo.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
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
	GLuint GetAmbientColorLocation() { return uniformDirectionalLight.base.color; }
	GLuint GetAmbientIntensityLocation() { return uniformDirectionalLight.base.ambientIntensity; }
	GLuint GetDiffuseIntensityLocation() { return uniformDirectionalLight.base.diffuseIntensity; }
	GLuint GetLightDirectionLocation() { return uniformDirectionalLight.direction; }
	GLuint GetSpecularLocation() { return uniformSpecular; }
	GLuint GetRoughnessLocation() { return uniformRoughness; }


	void SetDirectionalLight(DirectionalLight* dirLight);
	void SetPointLights(std::vector<PointLight>* pLight);
	void SetSpotLights(std::vector<SpotLight>* sLights);



	~Shader();

private:
	int pointLightCount;
	int spotLightCount;

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
		LightInfo<GLuint> base;
		GLuint direction;
	} uniformDirectionalLight;

	GLuint uniformPointLightCount;

	struct
	{
		GLuint position;
		LightInfo<GLuint> base;
		Quadratic<GLuint> attenuation;



	} uniformPointLight[MAX_POINT_LIGHTS];

	GLuint uniformSpotLightCount;
	struct
	{
		LightInfo<GLuint> base;
		Quadratic<GLuint> attenuation;
		GLuint position;
		GLuint direction;
		GLuint radius;
	} uniformSpotLight[MAX_SPOT_LIGHTS];

	void Compile(const char* vertexCode, const char* fragmentCode);
	void Add(GLuint program, const char* code, GLenum shaderType);
};

