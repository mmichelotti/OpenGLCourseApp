#include "Shader.h"
#include <GLM/glm.hpp>

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}
void Shader::SetDirectionalLight(DirectionalLight* dirLight)
{
	dirLight->Use(uniformDirectionalLight.base.color, uniformDirectionalLight.direction, uniformDirectionalLight.base.ambientIntensity, uniformDirectionalLight.base.diffuseIntensity);
}
void Shader::SetPointLights(std::vector<PointLight>* pLight, unsigned int textureUnit, unsigned int offset)
{
	unsigned int lightCount = glm::min((unsigned int)pLight->size(), (unsigned int)MAX_POINT_LIGHTS);
	glUniform1i(uniformPointLight->count, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		pLight->at(i).Use
		(
			uniformPointLight[i].base.color, 
			uniformPointLight[i].position, 
			uniformPointLight[i].base.ambientIntensity, 
			uniformPointLight[i].base.diffuseIntensity, 
			uniformPointLight[i].attenuation.constant, 
			uniformPointLight[i].attenuation.linear,
			uniformPointLight[i].attenuation.exponent
		);
		unsigned int currentLight = textureUnit + i;
		pLight->at(i).GetShadowMap()->Read(GL_TEXTURE0 + currentLight);
		glUniform1i(uniformOmniShadowMap[i + offset].shadowMap, currentLight);
		glUniform1f(uniformOmniShadowMap[i + offset].farPlane, pLight->at(i).GetFarPlane());
	}
}
void Shader::SetSpotLights(std::vector<SpotLight>* sLights, unsigned int textureUnit, unsigned int offset)
{
	unsigned int lightCount = glm::min((unsigned int)sLights->size(), (unsigned int)MAX_SPOT_LIGHTS);

	glUniform1i(uniformSpotLight->count, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		sLights->at(i).Use
		(
			uniformSpotLight[i].base.color, 
			uniformSpotLight[i].position, 
			uniformSpotLight[i].base.ambientIntensity, 
			uniformSpotLight[i].base.diffuseIntensity, 
			uniformSpotLight[i].attenuation.constant, 
			uniformSpotLight[i].attenuation.linear,
			uniformSpotLight[i].attenuation.exponent,
			uniformSpotLight[i].direction,
			uniformSpotLight[i].radius
		);

		unsigned int currentLight = textureUnit + i;
		sLights->at(i).GetShadowMap()->Read(GL_TEXTURE0 + currentLight);
		glUniform1i(uniformOmniShadowMap[i + offset].shadowMap, currentLight);
		glUniform1f(uniformOmniShadowMap[i + offset].farPlane, sLights->at(i).GetFarPlane());
	}
}
void Shader::SetTexture(GLuint textureUnit)
{
	glUniform1i(uniformTexture, textureUnit);

}
void Shader::SetDirectionalShadowMap(GLuint textureUnit)
{
	glUniform1i(uniformDirectionalShadowMap, textureUnit);
}
void Shader::SetDirectionalLightTransform(const glm::mat4& transform)
{
	glUniformMatrix4fv(uniformDirectionalLightTransform, 1, GL_FALSE, glm::value_ptr(transform));
}
void Shader::SetLightMatrices(std::vector<glm::mat4> lightMatrices)
{
	for (size_t i = 0; i < 6; i++)
	{
		glUniformMatrix4fv(uniformLightMatrices[i], 1, GL_FALSE, glm::value_ptr(lightMatrices[i]));
	}
}
Shader::~Shader()
{
	Clear();
}
void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	Compile(vertexCode, fragmentCode);
}

void Shader::CreateFromFile(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();
	Compile(vertexCode, fragmentCode);
}

void Shader::CreateFromFile(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string geometryString = ReadFile(geometryLocation);
	std::string fragmentString = ReadFile(fragmentLocation);

	const char* vertexCode = vertexString.c_str();
	const char* geometryCode = geometryString.c_str();
	const char* fragmentCode = fragmentString.c_str();
	Compile(vertexCode, geometryCode,fragmentCode);
}

void Shader::Validate()
{
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program, '%s \n", eLog);
		return;
	}
}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);
	if (!fileStream.is_open())
	{
		printf("Failed to read %s file doens't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void Shader::Use()
{
	glUseProgram(shaderID);
}

void Shader::Clear()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::Bind()
{
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program, '%s \n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

	uniformDirectionalLight.base.color = glGetUniformLocation(shaderID, "directionalLight.base.color");
	uniformDirectionalLight.base.ambientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.base.diffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	uniformDirectionalLight.direction = glGetUniformLocation(shaderID, "directionalLight.direction");

	uniformMaterial.specular = glGetUniformLocation(shaderID, "material.specular");
	uniformMaterial.roughness = glGetUniformLocation(shaderID, "material.roughness");

	uniformPointLight->count = glGetUniformLocation(shaderID, "pointLightCount");
	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
		uniformPointLight[i].base.color = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLight[i].base.ambientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLight[i].base.diffuseIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		uniformPointLight[i].position = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		uniformPointLight[i].attenuation.constant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		uniformPointLight[i].attenuation.linear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		uniformPointLight[i].attenuation.exponent = glGetUniformLocation(shaderID, locBuff);
	}

	uniformSpotLight->count = glGetUniformLocation(shaderID, "spotLightCount");
	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.color", i);
		uniformSpotLight[i].base.color = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
		uniformSpotLight[i].base.ambientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
		uniformSpotLight[i].base.diffuseIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
		uniformSpotLight[i].position = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
		uniformSpotLight[i].attenuation.constant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
		uniformSpotLight[i].attenuation.linear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
		uniformSpotLight[i].attenuation.exponent = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
		uniformSpotLight[i].direction = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
		uniformSpotLight[i].radius = glGetUniformLocation(shaderID, locBuff);
	}
	uniformTexture = glGetUniformLocation(shaderID, "theTexture");
	uniformDirectionalLightTransform = glGetUniformLocation(shaderID, "directionalLightTransform");
	uniformDirectionalShadowMap = glGetUniformLocation(shaderID, "directionalShadowMap");
	uniformOmniLightPos = glGetUniformLocation(shaderID, "lightPos");
	uniformFarPlane = glGetUniformLocation(shaderID, "farPlane");
	//refactor method of snprintf()
	for (size_t i = 0; i < 6; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "lightMatrices[%d]", i);
		uniformLightMatrices[i] = glGetUniformLocation(shaderID, locBuff);
	}
	for (size_t i = 0; i < MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%d].shadowMap", i);
		uniformOmniShadowMap[i].shadowMap = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%d].farPlane", i);
		uniformOmniShadowMap[i].farPlane = glGetUniformLocation(shaderID, locBuff);
	}
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();
	if (!shaderID)
	{
		printf("Can't create shader program");
		return;
	}

	Add(shaderID, vertexCode, GL_VERTEX_SHADER);
	Add(shaderID, fragmentCode, GL_FRAGMENT_SHADER);
	Bind();
}

void Shader::Compile(const char* vertexCode, const char* geometryCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();
	if (!shaderID)
	{
		printf("Can't create shader program");
		return;
	}

	Add(shaderID, vertexCode, GL_VERTEX_SHADER);
	Add(shaderID, geometryCode, GL_GEOMETRY_SHADER);
	Add(shaderID, fragmentCode, GL_FRAGMENT_SHADER);
	Bind();
}

void Shader::Add(GLuint program, const char* code, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	const GLchar* text[1];
	text[0] = code;

	GLint codeLength[1];
	codeLength[0] = strlen(code);

	glShaderSource(shader, 1, text, codeLength);
	glCompileShader(shader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader, '%s \n", shaderType, eLog);
		return;
	}

	glAttachShader(program, shader);

}
