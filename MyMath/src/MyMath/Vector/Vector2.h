#pragma once

struct Vector2
{
    float X;
    float Y;

    static float Dot(const Vector2& a, const Vector2& b);
    static Vector2 Normalized(const Vector2& v);

    void Normalize();
    float Magnitude() const;
};

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const Vector2& lhs, const float rhs);
Vector2 operator/(const Vector2& lhs, const float rhs);
void operator+=(Vector2& lhs, const Vector2& rhs);
void operator-=(Vector2& lhs, const Vector2& rhs);
void operator*=(Vector2& lhs, const float rhs);
void operator/=(Vector2& lhs, const float rhs);
