#pragma once
#include "D3D11.h"
#include <math.h>

struct Vector3
{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;

	Vector3()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}

	Vector3(FLOAT x, FLOAT y, FLOAT z) : X(x), Y(y), Z(z)
	{
		
	}

	Vector3 operator+(const Vector3& other)
	{
		Vector3 result;
		result.X = X + other.X; result.Y = Y + other.Y; result.Z = Z + other.Z;
		return result;
	}

	Vector3 operator-(const Vector3& other)
	{
		Vector3 result;
		result.X = X - other.X; result.Y = Y - other.Y; result.Z = Z - other.Z;
		return result;
	}

	Vector3 operator*(const float other)
	{
		Vector3 result;
		result.X = X * other; result.Y = Y * other; result.Z = Z * other;
		return result;
	}


	Vector3 operator/(const float other)
	{
		Vector3 result;
		result.X = X / other; result.Y = Y / other; result.Z = Z / other;
		return result;
	}

	void operator+=(const Vector3 other) { X += other.X; Y += other.Y; Z += other.Z; }
	void operator-=(const Vector3 other) { X -= other.X; Y -= other.Y; Z -= other.Z; }
	void operator*=(const float other) { X *= other; Y *= other; Z *= other; }
	void operator/=(const float other) { X /= other; Y /= other; Z /= other; }

	FLOAT Magnitude()
	{
		return sqrt(X * X + Y * Y + Z * Z);
	}

	void Normalize()
	{
		FLOAT mag = Magnitude();
		X /= mag;
		Y /= mag;
		Z /= mag;
	}

	static FLOAT Dot(Vector3 a, Vector3 b)
	{
		return a.X * b.X + a.Y * b.Y * a.Z * b.Z;
	}

	static Vector3 Cross(Vector3 a, Vector3 b)
	{
		Vector3 result;
		result.X = a.Y * b.Z - a.Z * b.Y;
		result.Y = a.Z * b.X - a.X * b.Z;
		result.Z = a.X * b.Y - a.Y * b.X;
		return result;
	}
};
