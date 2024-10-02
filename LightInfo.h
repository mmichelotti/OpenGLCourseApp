#pragma once
#include <GLM/glm.hpp>
template<typename T>
struct LightInfo
{
	T color;
	T ambientIntensity;
	T diffuseIntensity;
};