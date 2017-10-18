#include "stdafx.h"
#include "Vector3.h"

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

void operator+=(Vector3& lhs, const Vector3& rhs) { lhs.X += rhs.X; lhs.Y += rhs.Y; lhs.Z += rhs.Z; }
void operator-=(Vector3& lhs, const Vector3& rhs) { lhs.X -= rhs.X; lhs.Y -= rhs.Y; lhs.Z -= rhs.Z; }
void operator*=(Vector3& lhs, const float rhs) { lhs.X *= rhs; lhs.Y *= rhs; lhs.Z *= rhs; }
void operator/=(Vector3& lhs, const float rhs) { lhs.X /= rhs; lhs.Y /= rhs; lhs.Z /= rhs; }

FLOAT VectorMagnitude(Vector3& v)
{
	return sqrtf(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}

void VectorNormalize(Vector3& v)
{
	FLOAT mag = VectorMagnitude(v);
	v.X /= mag;
	v.Y /= mag;
	v.Z /= mag;
}

FLOAT VectorDot(Vector3 a, Vector3 b)
{
	return a.X * b.X + a.Y * b.Y * a.Z * b.Z;
}

Vector3 VectorCross(Vector3 a, Vector3 b)
{
	Vector3 result;
	result.X = a.Y * b.Z - a.Z * b.Y;
	result.Y = a.Z * b.X - a.X * b.Z;
	result.Z = a.X * b.Y - a.Y * b.X;
	return result;
}
