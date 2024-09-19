#include <GLFW/glfw3.h>
#include "Time.h"

float Time::_current = 0.0f;
float Time::_deltaTime = 0.0f;
float Time::_lastTime = 0.0f;

const float& Time::Current = Time::_current;
const float& Time::Delta = Time::_deltaTime;

void Time::UpdateTime()
{
	_current = glfwGetTime();
	_deltaTime = _current - _lastTime;
	_lastTime = _current;
}