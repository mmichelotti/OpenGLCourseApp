#include "Window.h"
#include <stdio.h>

Window::Window()
{
	width = 800;
	height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}


int Window::Initialise()
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
	window = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!window)
	{
		printf("GLFW can't create window");
		glfwTerminate();
		return 1;
	}

	//Get Buffer size information
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	//Set the context for GLEW to use
	glfwMakeContextCurrent(window);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	// Handle Key and Mouse inputs
	CreateCallbacks();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Initialize lastPos
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	lastPos = Vec2<GLfloat>(xPos, yPos);


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
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(window, this);
}
Vec2<GLfloat> Window::GetMouseDelta()
{
	Vec2<GLfloat> change = deltaPos;
	deltaPos = (0, 0);
	return change;
}


GLfloat Window::GetScrollOffset()
{
	GLfloat currentOffset = scrollOffset;
	scrollOffset = 0; 
	return currentOffset;
}
void Window::CreateCallbacks()
{
	glfwSetKeyCallback(window, HandleKeys);
	glfwSetCursorPosCallback(window, HandleMouse);
	glfwSetScrollCallback(window, HandleScroll);
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

void Window::HandleScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	currentWindow->scrollOffset = static_cast<GLfloat>(yoffset); // Either +1, -1, or 0
}


//! NEED TO CHANGE FIRST MOVE OR SOMETHING 
void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	currentWindow->deltaPos.x = xPos - currentWindow->lastPos.x;
	currentWindow->deltaPos.y = currentWindow->lastPos.y - yPos;
	currentWindow->lastPos = Vec2<GLint>(xPos, yPos);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
