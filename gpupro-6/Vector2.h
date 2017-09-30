#pragma once
#include "D3D11.h"
#include <math.h>

struct Vector2
{
	FLOAT X;
	FLOAT Y;

	Vector2 operator+(const Vector2& other) const
	{
		Vector2 result;
		result.X = X + other.X; result.Y = Y + other.Y;
		return result;
	}

	Vector2 operator-(const Vector2& other) const
	{
		Vector2 result;
		result.X = X - other.X; result.Y = Y - other.Y;
		return result;
	}

	Vector2 operator*(const float other) const
	{
		Vector2 result;
		result.X = X * other; result.Y = Y * other;
		return result;
	}


	Vector2 operator/(const float other) const
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

	static FLOAT Magnitude(Vector2& v)
	{
		return sqrt(v.X * v.X + v.Y * v.Y);
	}

	static void Normalize(Vector2& v)
	{
		FLOAT mag = Magnitude(v);
		v.X /= mag;
		v.Y /= mag;
	}

	static FLOAT Dot(Vector2 a, Vector2 b)
	{
		return a.X * b.X + a.Y * b.Y;
	}
};