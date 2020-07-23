#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

class vec2
{
public:
    vec2(float __x=0.f, float __y=0.f)
        : _x(__x), _y(__y)
    { }

    float x() const;
    float y() const;

    float length() const;

    vec2 operator+ (const vec2 &other);
    vec2 &operator+= (const vec2 &other);

    vec2 operator- (const vec2 &other);
    vec2 &operator-= (const vec2 &other);

    vec2 operator* (float a);
    vec2 operator/ (float a);

    bool operator ==(const vec2 &other);

private:
    float _x, _y;
};

class icolor
{

};

#endif
