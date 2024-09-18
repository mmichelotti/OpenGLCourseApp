#include "Window.h"
#include <stdio.h>

Window::Window()
{
	initialSize = Vec2<GLint>(800, 600);
	deltaPos = Vec2<GLfloat>(0, 0);
	for (int i = 0; i < 1024; i++) keys[i] = 0;
}

Window::Window(Vec2<GLint> windowSize)
{
	initialSize = windowSize;
	deltaPos = Vec2<GLfloat>(0, 0);
	for (int i = 0; i < 1024; i++) keys[i] = 0;
}
Window::Window(GLint windowX, GLint windowY)
{
	initialSize = Vec2<GLint>(windowX, windowY);
	deltaPos = Vec2<GLfloat>(0, 0);
	for (int i = 0; i < 1024; i++) keys[i] = 0;
}

int Window::Initialize()
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
	window = glfwCreateWindow(initialSize.x, initialSize.y, "Test Window", NULL, NULL);
	if (!window)
	{
		printf("GLFW can't create window");
		glfwTerminate();
		return 1;
	}

	//Get Buffer size information
	glfwGetFramebufferSize(window, &bufferSize.x, &bufferSize.y); //read the window and return width and height to our variables

	//Set the context for GLEW to use
	glfwMakeContextCurrent(window);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	// Handle Key and Mouse inputs
	//?TODO Move these inputs into their own static input class
	CreateCallbacks();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	//Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		printf("Can't Init GLEW");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	

	//Setup Viewport Size
	glViewport(0, 0, bufferSize.x, bufferSize.y);

	glfwSetWindowUserPointer(window, this);
}

Vec2<GLfloat> Window::GetChange()
{
	Vec2<GLfloat> change = deltaPos;
	deltaPos = (0, 0);
	return change;
}



void Window::CreateCallbacks()
{
	glfwSetKeyCallback(window, HandleKeys);
	glfwSetCursorPosCallback(window, HandleMouse);
}

void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			currentWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			currentWindow->keys[key] = false;
		}
	}
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (currentWindow->mouseFirstMoved)
	{
		currentWindow->lastPos = Vec2<GLint>(xPos, yPos);
		currentWindow->mouseFirstMoved = false;
	}
	currentWindow->deltaPos.x = xPos - currentWindow->lastPos.x;
	currentWindow->deltaPos.y = currentWindow->lastPos.y - yPos;
	currentWindow->lastPos = Vec2<GLint>(xPos, yPos);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
