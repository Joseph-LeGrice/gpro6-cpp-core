#include "Vector2.h"

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

float Vector2::Magnitude() const
{
	return sqrtf(X * X + Y * Y);
}

void Vector2::Normalize()
{
	float mag = Magnitude();
    X /= mag;
    Y /= mag;
}

float Vector2::Dot(const Vector2& a, const Vector2& b)
{
	return a.X * b.X + a.Y * b.Y;
}

Vector2 Vector2::Normalized(const Vector2& v)
{
    float mag = v.Magnitude();
    return { v.X / mag, v.Y / mag };
}
