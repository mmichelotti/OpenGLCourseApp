#pragma once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window();
	Window(GLint width, GLint height);

	int Initialize();

	GLfloat GetBufferWidth() { return bufferWidth; }
	GLfloat GetBufferHeight() { return bufferHeight; }
	GLfloat GetAspectRatio() { return bufferHeight / bufferHeight; }

	bool ShouldClose() { return glfwWindowShouldClose(window); }
	void SwapBuffers() { glfwSwapBuffers(window); }

	~Window();

private:
	GLFWwindow* window;
	GLint width, height;
	GLint bufferWidth, bufferHeight;
};

