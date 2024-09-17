#pragma once
#include <GL/glew.h>
#include <type_traits>

using namespace std;
template<typename T>
struct Vec2
{
public:
    T x, y;

    // Basic constructor
    Vec2(T x = T(), T y = T()) : x(x), y(y) {}

    // Copy constructor
    Vec2(const Vec2<T>& other) : x(other.x), y(other.y) {}

    // Conversion constructor
    template<typename U>
    Vec2(const Vec2<U>& other, typename enable_if<is_convertible<U, T>::value, U>::type* = 0)
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

    // Subtraction operator for Vec2
    template<typename U>
    Vec2<T> operator-(const Vec2<U>& other) const
    {
        static_assert(is_arithmetic<T>::value && is_arithmetic<U>::value, "T and U must be arithmetic types");
        return Vec2<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y));
    }
};