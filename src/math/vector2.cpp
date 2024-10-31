#include "genesis/math/vector2.hpp"

namespace genesis
{
Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2 Vector2::operator=(Vector2 &vector)
{
    x = vector.x;
    y = vector.y;
    return *this;
}

Vector2 Vector2::operator+(Vector2 &other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(Vector2 &other) const
{
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float number) const
{
    return Vector2(x * number, y * number);
}

Vector2 Vector2::operator/(float number) const
{
    return Vector2(x / number, y / number);
}

Vector2 Vector2::operator+=(Vector2 &vector)
{
    *this = this->operator+(vector);
    return *this;
}

Vector2 Vector2::operator-=(Vector2 &vector)
{
    *this = this->operator-(vector);
    return *this;
}

Vector2 Vector2::operator*=(float number)
{
    *this = this->operator*(number);
    return *this;
}

Vector2 Vector2::operator/=(float number)
{
    *this = this->operator/(number);
    return *this;
}
}
