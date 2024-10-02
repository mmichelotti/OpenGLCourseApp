#pragma once
#include <GLM/glm.hpp>
template<typename T>
struct Quadratic
{
	// Attenuation obtained by Color / by quadratic equation (ax^2 + bx + c)
	T constant;
	T linear;
	T exponent;

	Quadratic() :
		constant(1.0f), linear(0.0f), exponent(0.0f) {}
	Quadratic(T constant, T linear, T exponent) :
		constant(constant), linear(linear), exponent(exponent) {}
};