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
	GLfloat GetAspectRatio() { return bufferSize.x / bufferSize.y; }

	Vec2<GLfloat> GetChange();

	bool ShouldClose() { return glfwWindowShouldClose(window); }
	bool* GetKeys() { return keys; }
	void SwapBuffers() { glfwSwapBuffers(window); }

	~Window();

private:

	GLFWwindow* window;

	Vec2<GLint> initialSize;
	Vec2<GLint> bufferSize;

	bool keys[1024];
	bool mouseFirstMoved;

	Vec2<GLfloat> lastPos;
	Vec2<GLfloat> deltaPos;

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};

