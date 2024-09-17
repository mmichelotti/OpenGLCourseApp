#include "Vec2.h"

template<typename T>
Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}

template<typename T>
Vec2<T>::Vec2(const Vec2<T>& other) : x(other.x), y(other.y) {}

template<typename T>
template<typename U>
Vec2<T>::Vec2(const Vec2<U>& other, typename std::enable_if<std::is_convertible<U, T>::value, U>::type*)
    : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}