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
#include "DirectionalLight.h"
#include "Material.h"
#include "Global.h"
#include "PointLight.h"
#include "SpotLight.h"
#include <assimp/Importer.hpp>
#include "Model.h"
#include "Skybox.h"

/*
An index buffer is mostly identical to a vertex buffer
The core difference is that the index buffer groups the vertices that are overlapping
i.e. in the vertex buffer a cube is composed of 2 tris, which in total are 6 vertices
th Index Buffer recycle those overlapping vertices, so it has a total of 4
*/

GLuint uniformProjection = 0;
GLuint uniformModel = 0;
GLuint uniformView = 0;
GLuint uniformEyePosition = 0;
GLuint uniformOmniLightPos = 0;
GLuint uniformFarPlane = 0;
GLuint uniformSpecular = 0;
GLuint uniformRoughness = 0;

Window mainWindow;
Camera camera;
std::vector<Mesh*> meshes;

std::vector<Shader> shaders;
Shader directionalShadow;
Shader OmniShadow;

Texture brickTXT, dirtTXT, blankTXT;

Material roughMAT, dullMAT;

Skybox skybox;

Model blackhawk;
GLfloat blackhawkAngle = 0.0f;

DirectionalLight mainLight;
std::vector<PointLight> pointLights;
std::vector<SpotLight> spotLights;

void CreateShaders() 
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFile("Shaders/main.vert", "Shaders/main.frag");
	shaders.push_back(*shader1);
	directionalShadow = Shader();
	directionalShadow.CreateFromFile("Shaders/DirectionalShadowMap.vert", "Shaders/DirectionalShadowMap.frag");
	OmniShadow = Shader();
	OmniShadow.CreateFromFile("Shaders/OmniShadowMap.vert", "Shaders/OmniShadowMap.geom", "Shaders/OmniShadowMap.frag");
}
void RenderFrame()
{
	glm::mat4 model(1.0f);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brickTXT.Use();
	roughMAT.Use(uniformSpecular, uniformRoughness);
	meshes.at(0)->Render();


	model = glm::mat4(1.0f);
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brickTXT.Use();
	dullMAT.Use(uniformSpecular, uniformRoughness);
	meshes.at(1)->Render();

	blackhawkAngle += 0.1f;
	if (blackhawkAngle > 360) blackhawkAngle = 0.1f;

	blackhawk.transform.SetPosition(glm::vec3(-8.0f, 2.0f, 0.0f));
	blackhawk.transform.SetRotation(glm::vec3(-90.0f, blackhawkAngle, 0.0f));
	blackhawk.transform.SetScale(glm::vec3(0.4f, 0.4f, 0.4f));
	blackhawk.transform.UpdateModelMatrix(uniformModel);
	roughMAT.Use(uniformSpecular, uniformRoughness);
	blackhawk.Render();
}
void DirectionalShadowMapPass(DirectionalLight* dirLight)
{
	directionalShadow.Use();
	glViewport(0, 0, dirLight->GetShadowMap()->GetShadowWidth(), dirLight->GetShadowMap()->GetShadowHeight());
	dirLight->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);
	uniformModel = directionalShadow.GetModelLocation();
	directionalShadow.SetDirectionalLightTransform(dirLight->CalculateLightTransform());
	directionalShadow.Validate();
	RenderFrame();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OmnidirectionalShadowMapPass(PointLight* pLight)
{
	OmniShadow.Use();
	glViewport(0, 0, pLight->GetShadowMap()->GetShadowWidth(), pLight->GetShadowMap()->GetShadowHeight());
	pLight->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);
	uniformModel = OmniShadow.GetModelLocation();
	uniformOmniLightPos = OmniShadow.GetOmniLightPosLocation();
	uniformOmniLightPos = OmniShadow.GetOmniLightPosLocation();
	uniformFarPlane = OmniShadow.GetFarPlaneLocation();

	glUniform3f(uniformOmniLightPos, pLight->GetPosition().x, pLight->GetPosition().y, pLight->GetPosition().z);
	glUniform1f(uniformFarPlane, pLight->GetFarPlane());
	OmniShadow.SetLightMatrices(pLight->CalculateLightTransform());
	OmniShadow.Validate();
	RenderFrame();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	glViewport(0, 0, 1920, 1080);

	//Clear the whole window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Set it to white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear other pixel informations (in this case color and depth buffer)

	skybox.Draw(viewMatrix, projectionMatrix);

	shaders[0].Use();

	uniformModel = shaders[0].GetModelLocation();
	uniformProjection = shaders[0].GetProjectionLocation();
	uniformView = shaders[0].GetViewLocation();
	uniformEyePosition = shaders[0].GetEyePositionLocation();
	uniformSpecular = shaders[0].GetSpecularLocation();
	uniformRoughness = shaders[0].GetRoughnessLocation();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(uniformEyePosition, camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);

	spotLights.at(0).SetPositionAndDirection(camera.GetCameraPosition(), camera.GetCameraDirection());

	shaders[0].SetDirectionalLight(&mainLight);
	//shaders[0].SetPointLights(&pointLights, 3, 0);
	//shaders[0].SetSpotLights(&spotLights, 3 + pointLights.size(), pointLights.size());
	shaders[0].SetDirectionalLightTransform(mainLight.CalculateLightTransform());

	mainLight.GetShadowMap()->Read(GL_TEXTURE2);
	shaders[0].SetTexture(1);
	shaders[0].SetDirectionalShadowMap(2);
	shaders[0].Validate();
	RenderFrame();
}
int main()
{
	mainWindow = Window(1920, 1080);
	mainWindow.Initialize();
	camera = Camera(glm::vec3(0.0f, 4.0f, 4.0f), Vec2<GLfloat>(-90.0f, -45.0f));

	brickTXT = Texture("Textures/brick.png");
	brickTXT.LoadRGBA();
	dirtTXT = Texture("Textures/dirt.png");
	dirtTXT.LoadRGBA();
	blankTXT = Texture("Textures/plain.png");
	blankTXT.LoadRGBA();

	roughMAT = Material(1.0f, 512);
	dullMAT = Material(0.3f,4);

	blackhawk = Model();
	blackhawk.Load("Models/uh60.obj");

	mainLight = DirectionalLight(Light(Color(0.9f, 0.5f, 0.1f), 0.9f, 0.1f), 2048, glm::vec3(-10.0f, -12.0f, 18.5f));

	PointLight pLight1 = PointLight(Light(Color::Red, 0.4f, 0.1f), 2048, 100.0f, glm::vec3(-2.0f, 2.0f, 0.0f), Quadratic(0.3f, 0.2f, 0.1f));
	PointLight pLight2 = PointLight(Light(Color::Green, 0.4f, 0.1f), 2048, 100.0f, glm::vec3(2.0f, 2.0f, 0.0f), Quadratic(0.3f, 0.2f, 0.1f));
	pointLights.emplace_back(pLight1);
	pointLights.emplace_back(pLight2);
	SpotLight sLight1 = SpotLight(Light(Color::Blue, 1.0f, 1.0f), 2048, 100.0f, glm::vec3(-2.0f, 2.0f, 0.0f), Quadratic(0.3f, 0.2f, 0.1f), glm::vec3(0.0f, -1.0f, 0.0f), 20.0f);
	spotLights.emplace_back(sLight1);


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");
	skybox = Skybox(skyboxFaces);

	meshes.push_back(new Mesh(PYRAMID));
	meshes.push_back(new Mesh(PLANE));



	CreateShaders();

	glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.GetAspectRatio(), 0.1f, 100.0f);

	//Main Loop
	while (!mainWindow.ShouldClose())
	{
		Time::UpdateTime();
		glfwPollEvents(); //Get and handle user input events

		camera.KeyControl(mainWindow.GetKeys(), mainWindow.GetScrollDelta());
		camera.MouseControl(mainWindow.GetMouseDelta());

		DirectionalShadowMapPass(&mainLight);
		for (size_t i = 0; i < pointLights.size(); i++)
		{
			OmnidirectionalShadowMapPass(&pointLights[i]);
		}
		
		for (size_t i = 0; i < spotLights.size(); i++)
		{
			OmnidirectionalShadowMapPass(&spotLights[i]);
		}
		
		RenderPass(projection, camera.ViewMatrix());
		glUseProgram(0);
		mainWindow.SwapBuffers();
	}

	return 0;
}
