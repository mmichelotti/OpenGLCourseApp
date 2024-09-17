#pragma once
#include <GL/glew.h>
#include <type_traits>

template<typename T>
struct Vec2
{
    T x, y;

    Vec2(T x = 0, T y = 0)
    {
        this->x = x;
        this->y = y;
    }
    Vec2(const Vec2<T>& other)
    {
        x = other.x;
        y = other.y;
    }
};
