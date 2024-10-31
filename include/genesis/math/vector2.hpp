#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_MATH_VECTOR2_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_MATH_VECTOR2_HPP_

#include <cmath>

namespace genesis
{
struct Vector2
{
public:
    Vector2(float x = 0, float y = 0);
    Vector2(Vector2 &vector) : Vector2(vector.x, vector.y) { }
    Vector2(Vector2 &&vector) : Vector2(vector.x, vector.y) { }

    float Magnitude() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2)); }
    float SquaredMagnitude() const { return std::pow(Magnitude(), 2); }
    Vector2 Normalized() const { return *this / Magnitude(); }

    Vector2 operator=(Vector2 &vector);
    Vector2 operator=(Vector2 &&vector) { return operator=(vector); }


    Vector2 operator+(Vector2 &other) const;
    Vector2 operator+(Vector2 &&other) const { return operator+(other); }

    Vector2 operator-(Vector2 &other) const;
    Vector2 operator-(Vector2 &&other) const { return operator-(other); }

    Vector2 operator*(float number) const;
    Vector2 operator/(float number) const;

    friend Vector2 operator*(float number, Vector2 vector) { return vector.operator*(number); }
    friend Vector2 operator/(float number, Vector2 vector) { return vector.operator/(number); }


    Vector2 operator+=(Vector2 &vector);
    Vector2 operator+=(Vector2 &&vector) { return operator+=(vector); }

    Vector2 operator-=(Vector2 &vector);
    Vector2 operator-=(Vector2 &&vector) { return operator-=(vector); }

    Vector2 operator*=(float number);
    Vector2 operator/=(float number);

    friend Vector2 operator*=(float number, Vector2 vector) { return vector.operator*=(number); }
    friend Vector2 operator/=(float number, Vector2 vector) { return vector.operator/=(number); }

    float x;
    float y;
};
}

#endif
