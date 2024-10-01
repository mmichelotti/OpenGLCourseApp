#include "Shader.h"
#include <GLM/glm.hpp>

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;

	pointLightCount = 0;
}
void Shader::SetDirectionalLight(DirectionalLight* dirLight)
{
	dirLight->Use(uniformDirectionalLight.color, uniformDirectionalLight.direction, uniformDirectionalLight.ambientIntensity, uniformDirectionalLight.diffuseIntensity);
}
void Shader::SetPointLights(std::vector<PointLight>* pLight)
{
	unsigned int lightCount = glm::min(pLight->size(), MAX_POINT_LIGHTS);

	glUniform1i(uniformPointLightCount, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		pLight->at(i).Use(uniformPointLight[i].color, uniformPointLight[i].position, uniformPointLight[i].ambientIntensity, uniformPointLight[i].diffuseIntensity, uniformPointLight[i].constant, uniformPointLight[i].linear, uniformPointLight[i].exponent);
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
	glValidateProgram(shaderID);

	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program, '%s \n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

	uniformDirectionalLight.color = glGetUniformLocation(shaderID, "directionalLight.base.color");
	uniformDirectionalLight.ambientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.diffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	uniformDirectionalLight.direction = glGetUniformLocation(shaderID, "directionalLight.direction");

	uniformSpecular = glGetUniformLocation(shaderID, "material.specular");
	uniformRoughness = glGetUniformLocation(shaderID, "material.roughness");

	uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = {'\0'};

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
		uniformPointLight[i].color = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLight[i].ambientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLight[i].diffuseIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		uniformPointLight[i].position = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		uniformPointLight[i].constant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		uniformPointLight[i].linear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		uniformPointLight[i].exponent = glGetUniformLocation(shaderID, locBuff);
	}

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
