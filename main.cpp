#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"

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
const float toRadians = 3.14159265f / 180.0f; //converting a full circle from 2PI to 360*



/*
An index buffer is mostly identical to a vertex buffer
The core difference is that the index buffer groups the vertices that are overlapping
i.e. in the vertex buffer a cube is composed of 2 tris, which in total are 6 vertices 
th Index Buffer recycle those overlapping vertices, so it has a total of 4
*/

std::vector<Mesh*> meshes;
std::vector<Shader> shaders;


bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.0005f;

float curAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;



//Vertex Shader
static const char* vShader = "Shaders/shader.vert";

//Fragment  Shader
static const char* fShader = "Shaders/shader.frag";

void CreateObjects() 
{
	//switched from tri to pyramid

	unsigned int indices[] =
	{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};
	
	GLfloat vertices[] =
	{
		-1.0f, -1.0f, 0.0f,
		 0.0f, -1.0f, 1.0f,
	     1.0,  -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};
	Mesh* obj = new Mesh();
	obj->Create(vertices, indices, 12,12);
	//-> this syntax is like "." the differnece is that since obj is a pointer, this is the syntax to access its public members
	meshes.push_back(obj);
}



void CreateShaders() 
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFile(vShader, fShader);
	shaders.push_back(*shader1);
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

	glEnable(GL_DEPTH_TEST);

	//Setup Viewport Size
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);

	//Main Loop
	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents(); //Get and handle user input events

		if (direction) triOffset += triIncrement;
		else triOffset -= triIncrement;
		if (abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;
			sizeDirection = !sizeDirection;
		}

		curAngle += 0.01f;
		if (curAngle >= 360) curAngle -= 360;

		if (sizeDirection) curSize += 0.0001f;
		else curSize -= 0.0001f;


		//Clear the whole window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Set it to white
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear other pixel informations (in this case color and depth buffer)

		//Bind shader
		shaders[0].Use();
		uniformModel = shaders[0].GetModelLocation();
		uniformProjection = shaders[0].GetProjectionLocation();

		
		glm::mat4 model(1.0f); //create identity matrix 
			//1 0 0 0 
			//0 1 0 0
			//0 0 1 0
			//0 0 0 1
		model = glm::translate(model, glm::vec3(0.0f, triOffset*3, -5.0f)); //translate the uniform further so we can see it on the projection matrix
			//uniform variables are a constant through all the shader, not influenced by each single vertex

		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); //rotate n degrees around the z axis
			//of course the objects distorts becuase there is no projection matrix applied to the geometry
			//the default matrix system is the window coordinate system, so as we rotate an object on a non uniform window
			//the object will deform to match the window coordynate system
		//model = glm::scale(model, glm::vec3(curSize, curSize, 1.0f));
			//so the order matters, even when scaling
			//to make translations absolute we need to apply them first
			//if we want them relative we need to apply after



		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshes[0]->Render();

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}
