#pragma once
#include "D3D11.h"
#include <math.h>

struct Vector2
{
	FLOAT X;
	FLOAT Y;

	Vector2 operator+(const Vector2& other)
	{
		Vector2 result;
		result.X = X + other.X; result.Y = Y + other.Y;
		return result;
	}

	Vector2 operator-(const Vector2& other)
	{
		Vector2 result;
		result.X = X - other.X; result.Y = Y - other.Y;
		return result;
	}

	Vector2 operator*(const float other)
	{
		Vector2 result;
		result.X = X * other; result.Y = Y * other;
		return result;
	}


	Vector2 operator/(const float other)
	{
		Vector2 result;
		result.X = X / other; result.Y = Y / other;
		return result;
	}

	void operator+=(const Vector2 other) { X += other.X; Y += other.Y; }
	void operator-=(const Vector2 other) { X -= other.X; Y -= other.Y; }
	void operator*=(const float other) { X *= other; Y *= other; }
	void operator/=(const float other) { X /= other; Y /= other; }

	static Vector2 Zero()
	{
		return{ 0, 0 };
	}

	FLOAT Magnitude()
	{
		return sqrt(X * X + Y * Y);
	}

	void Normalize()
	{
		FLOAT mag = Magnitude();
		X /= mag;
		Y /= mag;
	}

	static FLOAT Dot(Vector2 a, Vector2 b)
	{
		return a.X * b.X + a.Y * b.Y;
	}
};