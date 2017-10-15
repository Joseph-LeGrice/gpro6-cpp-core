#pragma once
#include <math.h>

struct Vector2
{
	FLOAT X;
	FLOAT Y;
};

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const Vector2& lhs, const float rhs);
Vector2 operator/(const Vector2& lhs, const float rhs);
void operator+=(Vector2& lhs, const Vector2& rhs);
void operator-=(Vector2& lhs, const Vector2& rhs);
void operator*=(Vector2& lhs, const float rhs);
void operator/=(Vector2& lhs, const float rhs);
FLOAT VectorMagnitude(const Vector2& v);
void VectorNormalize(Vector2& v);
FLOAT VectorDot(const Vector2& a, const Vector2& b);