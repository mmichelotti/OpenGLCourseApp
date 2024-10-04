#pragma once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();

	GLint GetBufferWidth() { return bufferWidth; }
	GLint GetBufferHeight() { return bufferHeight; }

	GLfloat GetScrollOffset();
	//Vec2<GLfloat> GetMouseDelta();
	GLfloat getXChange();
	GLfloat getYChange();
	

	bool ShouldClose() { return glfwWindowShouldClose(window); }
	bool* GetKeys() { return keys; }
	void SwapBuffers() { glfwSwapBuffers(window); }

	~Window();

private:

	GLFWwindow* window;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024] = {};

	GLfloat lastX, lastY;
	GLfloat xChange, yChange;
	GLfloat scrollOffset = 0;

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleScroll(GLFWwindow* window, double xoffset, double yoffset);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};

