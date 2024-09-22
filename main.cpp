#define STB_IMAGE_IMPLEMENTATION

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
#include "Window.h"
#include "Camera.h"
#include "Time.h"
#include "Texture.h"
#include "Light.h"

//GL => The actual graphics API
//GLEW => OpenGL Extensions for additional OpenGL features and extensions, since OpenGL can differ across platforms
//GLFW => Windows and input management
/*
GLFW (Graphics Library Framework) is responsible for creating and managing windows, 
handling input (keyboard, mouse), and managing OpenGL contexts. 
It doesn't interact with OpenGL directly to render graphics but helps set up the environment to use OpenGL. 
It provides a platform-independent API for windowing and input.
*/

const float toRadians = 3.14159265f / 180.0f; //converting a full circle from 2PI to 360*

//Vertex and Fragment Shader files
static const char* vShader = "Shaders/shader.vert";
static const char* fShader = "Shaders/shader.frag";

/*
An index buffer is mostly identical to a vertex buffer
The core difference is that the index buffer groups the vertices that are overlapping
i.e. in the vertex buffer a cube is composed of 2 tris, which in total are 6 vertices 
th Index Buffer recycle those overlapping vertices, so it has a total of 4
*/

Window mainWindow;
Camera camera;
std::vector<Mesh*> meshes;
std::vector<Shader> shaders;


Texture brickTXT;
Texture dirtTXT;

Light mainLight;

std::vector<unsigned int> indices = {
	0, 3, 1,
	1, 3, 2,
	2, 3, 0,
	0, 1, 2
};

std::vector<GLfloat> vertices = 
{
//    x      y     z     u     v
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	 0.0f, -1.0f, 1.0f,	0.5f, 0.0f,
	 1.0f, -1.0f, 0.0f,	1.0f, 0.0f,
	 0.0f,  1.0f, 0.0f,	0.5f, 1.0f
};


void AddMesh(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices)
{
	meshes.push_back(new Mesh(vertices, indices));
}

void CreateShaders() 
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFile(vShader, fShader);
	shaders.push_back(*shader1);
}
int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialize();
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), Vec2<GLfloat>(-90.0f, 0.0f), 5.0f, 0.5f);

	brickTXT = Texture("Textures/brick.png");
	brickTXT.Load();
	dirtTXT = Texture("Textures/dirt.png");
	dirtTXT.Load();

	mainLight = Light(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);

	AddMesh(vertices, indices);
	AddMesh(vertices, indices);
	AddMesh(vertices, indices);

	CreateShaders();

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformAmbientColor = 0;
	GLuint uniformAmbientIntensity = 0;

	glm::mat4 projection = glm::perspective(45.0f, mainWindow.GetAspectRatio(), 0.1f, 100.0f);
	
	//Main Loop
	while (!mainWindow.ShouldClose())
	{
		Time::UpdateTime();
		glfwPollEvents(); //Get and handle user input events

		camera.KeyControl(mainWindow.GetKeys(), mainWindow.GetScrollOffset());
		camera.MouseControl(mainWindow.GetMouseDelta());

		//Clear the whole window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Set it to white
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear other pixel informations (in this case color and depth buffer)

		//Bind shader
		shaders[0].Use();
		uniformModel = shaders[0].GetModelLocation();
		uniformProjection = shaders[0].GetProjectionLocation();
		uniformView = shaders[0].GetViewLocation();
		uniformAmbientColor = shaders[0].GetAmbientColorLocation();
		uniformAmbientIntensity = shaders[0].GetAmbientIntensityLocation();

		mainLight.Use(uniformAmbientIntensity, uniformAmbientColor);


		//Identity Matrix 
		/*
			1 0 0 0 
			0 1 0 0
			0 0 1 0
			0 0 0 1
		*/
		//Uniform variables are a constant through all the shader, not influenced by each single vertex
		/* 
			Of course the objects distorts becuase there is no projection matrix applied to the geometry
			the default matrix system is the window coordinate system, so as we rotate an object on a non uniform window
			the object will deform to match the window coordynate system
			
			so the order matters, even when scaling
			to make translations absolute we need to apply them first
			if we want them relative we need to apply after
		*/

		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.ViewMatrix()));
		brickTXT.Use();
		meshes[0]->Render();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTXT.Use();
		meshes[1]->Render();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshes[2]->Render();

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	return 0;
}
