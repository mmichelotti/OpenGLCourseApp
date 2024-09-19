#pragma once
static class Time
{
public:
	static const float& Current;
	static const float& Delta;
	static void UpdateTime();
private:
	static float _current;
	static float _lastTime;
	static float _deltaTime;
};