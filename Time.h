#pragma once
#include <GLFW/glfw3.h>
static class Time
{
public:
	static float GetTime() { return time; }
	static float GetDeltaTime() { return deltaTime; }
	static float GetLastTime() { return lastTime; }
	static void UpdateTime();
private:
	static float time;
	static float lastTime;
	static float deltaTime;
};