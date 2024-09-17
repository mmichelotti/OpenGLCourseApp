#pragma once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Vectors.h"

class Window
{
public:
	Window();
	Window(Vec2<GLint> windowSize);
	Window(GLint windowX, GLint windowY);

	int Initialize();

	GLfloat GetBufferWidth() { return buffer.x; }
	GLfloat GetBufferHeight() { return buffer.y; }
	GLfloat GetAspectRatio() { return buffer.x / buffer.y; }

	bool ShouldClose() { return glfwWindowShouldClose(window); }
	void SwapBuffers() { glfwSwapBuffers(window); }

	~Window();

private:
	GLFWwindow* window;

	Vec2<GLint> initialSize;
	Vec2<GLint> buffer;

	bool keys[1024];

	Vec2<GLfloat> lastPos;
	Vec2<GLfloat> changedPos;


	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
};

