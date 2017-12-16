#include "stdafx.h"
#include "Core/DataStructures/Vector2.h"

#include <math.h>

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 result;
	result.X = lhs.X + rhs.X; result.Y = lhs.Y + rhs.Y;
	return result;
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 result;
	result.X = lhs.X - rhs.X; result.Y = lhs.Y - rhs.Y;
	return result;
}

Vector2 operator*(const Vector2& lhs, const float rhs)
{
	Vector2 result;
	result.X = lhs.X * rhs; result.Y = lhs.Y * rhs;
	return result;
}


Vector2 operator/(const Vector2& lhs, const float rhs)
{
	Vector2 result;
	result.X = lhs.X / rhs; result.Y = lhs.Y / rhs;
	return result;
}

void operator+=(Vector2& lhs, const Vector2& rhs) { lhs.X += rhs.X; lhs.Y += rhs.Y; }
void operator-=(Vector2& lhs, const Vector2& rhs) { lhs.X -= rhs.X; lhs.Y -= rhs.Y; }
void operator*=(Vector2& lhs, const float rhs) { lhs.X *= rhs; lhs.Y *= rhs; }
void operator/=(Vector2& lhs, const float rhs) { lhs.X /= rhs; lhs.Y /= rhs; }

FLOAT Vector2::Magnitude(const Vector2& v)
{
	return sqrtf(v.X * v.X + v.Y * v.Y);
}

void Vector2::Normalize(Vector2& v)
{
	FLOAT mag = Vector2::Magnitude(v);
	v.X /= mag;
	v.Y /= mag;
}

FLOAT Vector2::Dot(const Vector2& a, const Vector2& b)
{
	return a.X * b.X + a.Y * b.Y;
}
