#pragma once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Vec2.h"

class Window
{
public:
	Window();
	Window(Vec2<GLint> windowSize);
	Window(GLint windowX, GLint windowY);

	int Initialize();

	GLfloat GetBufferWidth() { return bufferSize.x; }
	GLfloat GetBufferHeight() { return bufferSize.y; }
	GLfloat GetAspectRatio() { return (GLfloat)bufferSize.x / bufferSize.y; }

	GLfloat GetScrollOffset();
	Vec2<GLfloat> GetMouseDelta();
	

	bool ShouldClose() { return glfwWindowShouldClose(window); }
	bool* GetKeys() { return keys; }
	void SwapBuffers() { glfwSwapBuffers(window); }

	~Window();

private:

	GLFWwindow* window;

	Vec2<GLint> initialSize;
	Vec2<GLint> bufferSize;

	bool keys[1024] = {};

	GLfloat lastScroll = 0;
	GLfloat scrollOffset = 0;

	Vec2<GLfloat> lastPos;
	Vec2<GLfloat> deltaPos = Vec2<GLfloat>(0, 0);

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleScroll(GLFWwindow* window, double xoffset, double yoffset);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};

