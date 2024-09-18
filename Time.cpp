#include <GLFW/glfw3.h>
#include "Time.h"

float Time::time = 0.0f;
float Time::deltaTime = 0.0f;
float Time::lastTime = 0.0f;

void Time::UpdateTime()
{
	time = glfwGetTime();
	deltaTime = time - lastTime;
	lastTime = time;
}