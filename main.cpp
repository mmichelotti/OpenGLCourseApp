#include <stdio.h>
#include <string.h>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


//GL => The actual graphics API
//GLEW => OpenGL Extensions for additional OpenGL features and extensions, since OpenGL can differ across platforms
//GLFW => Windows and input management
/*
GLFW (Graphics Library Framework) is responsible for creating and managing windows, 
handling input (keyboard, mouse), and managing OpenGL contexts. 
It doesn't interact with OpenGL directly to render graphics but helps set up the environment to use OpenGL. 
It provides a platform-independent API for windowing and input.
*/

const GLint WIDTH = 800, HEIGHT = 600;
GLuint VAO; //Vertex Array Object, it will hjold multiple VBO and other types of buffer
GLuint VBO; //Vertex Buffer Object
GLuint shader;
GLuint uniformXMove;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.0005f;

//Vertex Shader
static const char* vShader = 
"																							\n\
#version 330																				\n\
																							\n\
layout (location = 0) in vec3 pos;															\n\
																							\n\
uniform float xMove;																						\n\
																							\n\
void main()																					\n\
{																							\n\
		gl_Position = vec4(pos.xyz/2 + xMove, 1.0);													\n\
}																							\n\
";

//Fragment  Shader
static const char* fShader =
"																							\n\
#version 330																				\n\
																							\n\
out vec4 color;																				\n\
void main()																					\n\
{																							\n\
		color = vec4(1.0,0.0,0.0,1.0);													    \n\
}																							\n\
";


void CreateTriangle() 
{
	GLfloat vertices[] =
	{
		-1.0f, -1.0f, 0.0f,
	     1.0,  -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};
	//generate and bind VAO and VBO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//Unbind VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void AddShader(GLuint program, const char* code, GLenum shaderType) 
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


void CompileShaders() 
{
	shader = glCreateProgram();
	if (!shader) 
	{
		printf("Can't create shader program");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if(!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program, '%s \n", eLog);
		return;
	}
	glValidateProgram(shader);

	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program, '%s \n", eLog);
		return;
	}

	uniformXMove = glGetUniformLocation(shader, "xMove");
}


int main()
{
	//Initialize GLFW 
	if (!glfwInit())
	{
		printf("Can't Init GLFW");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW Window Properties to v3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // No backwards compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Yes forward compatibility
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW can't create window");
		glfwTerminate();
		return 1;
	}

	//Get Buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight); //read the window and return width and height to our variables

	//Set the context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	//Allow modern extension features
	glewExperimental = GL_TRUE;


	//Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		printf("Can't Init GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	//Setup Viewport Size
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateTriangle();
	CompileShaders();

	//Main Loop
	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents(); //Get and handle user input events

		if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}
		if (abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;
		}
		//Clear the whole window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Set it to white
		glClear(GL_COLOR_BUFFER_BIT); //Clear other pixel informations (a pixel contains more than colors)

		//Bind shader and VAO
		glUseProgram(shader);
		glUniform1f(uniformXMove,triOffset);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);


		//Unbind shader and VAO
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}