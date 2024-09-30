#include "Color.h"
#include <iostream>
#include <algorithm> 

const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);

Color::Color() :
    r(0.0f),
    g(0.0f),
    b(0.0f),
    a(1.0f) {}

// Constructor definition
Color::Color(float r, float g, float b, float a) : 
    r(saturate(r)), 
    g(saturate(g)), 
    b(saturate(b)), 
    a(saturate(a)) {}

// Clamp function
float Color::saturate(float value) const { return std::clamp(value, 0.0f, 1.0f); }
