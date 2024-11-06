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
#include "Global.h"
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/glm.hpp>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFile(const char* vertexLocation, const char* fragmentLocation);
	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation() { return uniformProjection; }
	GLuint GetModelLocation() { return uniformModel; }
	GLuint GetViewLocation() { return uniformView; }
	GLuint GetEyePositionLocation() { return uniformEyePosition; }
	GLuint GetAmbientColorLocation() { return uniformDirectionalLight.base.color; }
	GLuint GetAmbientIntensityLocation() { return uniformDirectionalLight.base.ambientIntensity; }
	GLuint GetDiffuseIntensityLocation() { return uniformDirectionalLight.base.diffuseIntensity; }
	GLuint GetLightDirectionLocation() { return uniformDirectionalLight.direction; }
	GLuint GetSpecularLocation() { return uniformMaterial.specular; }
	GLuint GetRoughnessLocation() { return uniformMaterial.roughness; }

	void Use();
	void Clear();
	void SetDirectionalLight(DirectionalLight* dirLight);
	void SetPointLights(std::vector<PointLight>* pLight);
	void SetSpotLights(std::vector<SpotLight>* sLights);
	void SetTexture(GLuint textureUnit);
	void SetDirectionalShadowMap(GLuint textureUnit);
	void SetDirectionalLightTransform(const glm::mat4& transform);


	~Shader();

private:

	GLuint shaderID;
	GLuint uniformProjection;
	GLuint uniformModel;
	GLuint uniformView;
	GLuint uniformEyePosition;
	GLuint uniformTexture;
	GLuint uniformDirectionalLightTransform, uniformDirectionalShadowMap;


	struct
	{
		GLuint specular;
		GLuint roughness;
	} uniformMaterial;

	struct UniformLight
	{
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;
	};
	struct
	{
		UniformLight base;
		GLuint direction;
	} uniformDirectionalLight;

	struct
	{
		UniformLight base;
		GLuint count;
		GLuint position;
		Quadratic<GLuint> attenuation;

	} uniformPointLight[MAX_POINT_LIGHTS];

	struct
	{
		UniformLight base;
		GLuint count;
		Quadratic<GLuint> attenuation;
		GLuint position;
		GLuint direction;
		GLuint radius;

	} uniformSpotLight[MAX_SPOT_LIGHTS];

	void Compile(const char* vertexCode, const char* fragmentCode);
	void Add(GLuint program, const char* code, GLenum shaderType);
};

