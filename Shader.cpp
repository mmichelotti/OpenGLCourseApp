#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}
Shader::~Shader()
{
	Clear();
}
void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	Compile(vertexCode, fragmentCode);

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
