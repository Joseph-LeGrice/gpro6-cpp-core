#pragma once

struct Vector3
{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
};

Vector3 operator+(const Vector3& first, const Vector3& second);
Vector3 operator-(const Vector3& rhs);
Vector3 operator-(const Vector3& rhs, const Vector3& second);
Vector3 operator*(const Vector3& first, const float factor);
Vector3 operator*(const float rhs, Vector3& lhs);
Vector3 operator/(const Vector3& first, const float factor);
void operator+=(Vector3& lhs, const Vector3& rhs);
void operator-=(Vector3& lhs, const Vector3& rhs);
void operator*=(Vector3& lhs, const float rhs);
void operator/=(Vector3& lhs, const float rhs);

FLOAT VectorMagnitude(Vector3& v);
void VectorNormalize(Vector3& v);
FLOAT VectorDot(Vector3 a, Vector3 b);
Vector3 VectorCross(Vector3 a, Vector3 b);