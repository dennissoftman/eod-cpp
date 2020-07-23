#include "include/primitives.hpp"
#include <cmath>
#include <limits>

float vec2::x() const
{
    return _x;
}

float vec2::y() const
{
    return _y;
}

float vec2::length() const
{
    return sqrtf(_x*_x +  _y*_y);
}

vec2 vec2::operator+ (const vec2 &other)
{
    return vec2(_x + other._x, _y + other._y);
}

vec2 &vec2::operator+= (const vec2 &other)
{
    _x += other._x;
    _y += other._y;
    return *this;
}

vec2 vec2::operator- (const vec2 &other)
{
    return vec2(_x - other._x, _y - other._y);
}

vec2 &vec2::operator-= (const vec2 &other)
{
    _x -= other._x;
    _y -= other._y;
    return *this;
}

vec2 vec2::operator* (float a)
{
    return vec2(_x*a, _y*a);
}

vec2 vec2::operator/ (float a)
{
    if(a == 0.f)
        return vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    return vec2(_x/a, _y/a);
}

bool vec2::operator ==(const vec2 &other)
{
    return (_x == other._x) and (_y == other._y);
}
