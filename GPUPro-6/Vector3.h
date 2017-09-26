#pragma once
#include "D3D11.h"
#include <math.h>

struct Vector3
{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;

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

	static Vector3 New(FLOAT x, FLOAT y, FLOAT z)
	{
		return { x, y, z };
	}

	static Vector3 Zero()
	{
		return{ 0.0f, 0.0f, 0.0f };
	}

	static Vector3 One()
	{
		return{ 1.0f, 1.0f, 1.0f };
	}
	
	static FLOAT Magnitude(Vector3& v)
	{
		return sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
	}

	static void Normalize(Vector3& v)
	{
		FLOAT mag = Magnitude(v);
		v.X /= mag;
		v.Y /= mag;
		v.Z /= mag;
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
