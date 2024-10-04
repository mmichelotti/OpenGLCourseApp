#pragma once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Vec2.h"

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();

	GLint GetBufferWidth() { return bufferWidth; }
	GLint GetBufferHeight() { return bufferHeight; }
	GLfloat GetAspectRatio() { return (GLfloat)bufferWidth / (GLfloat)bufferHeight; }

	GLfloat GetScrollOffset();
	Vec2<GLfloat> GetMouseDelta();

	bool ShouldClose() { return glfwWindowShouldClose(window); }
	bool* GetKeys() { return keys; }
	void SwapBuffers() { glfwSwapBuffers(window); }

	~Window();

private:

	GLFWwindow* window;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024] = {};

	GLfloat scrollOffset = 0;

	Vec2<GLfloat> lastPos = Vec2<GLfloat>(0, 0);
	Vec2<GLfloat> deltaPos = Vec2<GLfloat>(0, 0);


	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleScroll(GLFWwindow* window, double xoffset, double yoffset);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};