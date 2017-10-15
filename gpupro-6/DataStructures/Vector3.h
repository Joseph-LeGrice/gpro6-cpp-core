#pragma once
#include "D3D11.h"
#include <math.h>

struct Vector3
{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
};

Vector3 operator+(const Vector3& first, const Vector3& second);
Vector3 operator-(const Vector3& first);
Vector3 operator-(const Vector3& first, const Vector3& second);
Vector3 operator*(const Vector3& first, const float factor);
Vector3 operator/(const Vector3& first, const float factor);
void operator+=(Vector3& lhs, const Vector3& rhs);
void operator-=(Vector3& lhs, const Vector3& rhs);
void operator*=(Vector3& lhs, const float rhs);
void operator/=(Vector3& lhs, const float rhs);
Vector3 VectorNew(FLOAT x, FLOAT y, FLOAT z);
Vector3 VectorZero();
Vector3 VectorOne();
Vector3 VectorUp();
FLOAT VectorMagnitude(Vector3& v);
void VectorNormalize(Vector3& v);
FLOAT VectorDot(Vector3 a, Vector3 b);
Vector3 VectorCross(Vector3 a, Vector3 b);