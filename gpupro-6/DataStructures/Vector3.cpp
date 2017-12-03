#include "stdafx.h"
#include "Vector3.h"
#include "Quaternion.h"

#include <math.h>

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 result;
	result.X = lhs.X + rhs.X; result.Y = lhs.Y + rhs.Y; result.Z = lhs.Z + rhs.Z;
	return result;
}

Vector3 operator-(const Vector3& rhs)
{
	Vector3 result;
	result.X = -rhs.X; result.Y = -rhs.Y; result.Z = -rhs.Z;
	return result;
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 result;
	result.X = lhs.X - rhs.X; result.Y = lhs.Y - rhs.Y; result.Z = lhs.Z - rhs.Z;
	return result;
}

Vector3 operator*(const Vector3& lhs, const float rhs)
{
	Vector3 result;
	result.X = lhs.X * rhs; result.Y = lhs.Y * rhs; result.Z = lhs.Z * rhs;
	return result;
}

Vector3 operator*(const float lhs, Vector3& rhs)
{
	Vector3 result;
	result.X = rhs.X * lhs; result.Y = rhs.Y * lhs; result.Z = rhs.Z * lhs;
	return result;
}

Vector3 operator/(const Vector3& first, const float factor)
{
	Vector3 result;
	result.X = first.X / factor; result.Y = first.Y / factor; result.Z = first.Z / factor;
	return result;
}

void operator*=(Vector3& lhs, Quaternion rhs)
{
    //TODO: Implement
}

void operator+=(Vector3& lhs, const Vector3& rhs) { lhs.X += rhs.X; lhs.Y += rhs.Y; lhs.Z += rhs.Z; }
void operator-=(Vector3& lhs, const Vector3& rhs) { lhs.X -= rhs.X; lhs.Y -= rhs.Y; lhs.Z -= rhs.Z; }
void operator*=(Vector3& lhs, const float rhs) { lhs.X *= rhs; lhs.Y *= rhs; lhs.Z *= rhs; }
void operator/=(Vector3& lhs, const float rhs) { lhs.X /= rhs; lhs.Y /= rhs; lhs.Z /= rhs; }

FLOAT Vector3::Magnitude(Vector3& v)
{
	return sqrtf(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}

void Vector3::Normalize(Vector3& v)
{
	FLOAT mag = Vector3::Magnitude(v);
    if (mag > 0)
    {
        v.X /= mag;
        v.Y /= mag;
        v.Z /= mag;
    }
}

FLOAT Vector3::Dot(Vector3 a, Vector3 b)
{
	return a.X * b.X + a.Y * b.Y * a.Z * b.Z;
}

Vector3 Vector3::Cross(Vector3 a, Vector3 b)
{
	Vector3 result;
	result.X = a.Y * b.Z - a.Z * b.Y;
	result.Y = a.Z * b.X - a.X * b.Z;
	result.Z = a.X * b.Y - a.Y * b.X;
	return result;
}
