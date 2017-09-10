#pragma once

#include "Vector3.h"

struct Quaternion
{
	FLOAT W;
	Vector3 V;

	Quaternion()
	{
		W = 1.0f;
		V = {0.0, 0.0, 0.0};
	}

	static Quaternion FromAxisAngle(Vector3 axis, float angle)
	{
		Quaternion q;
		q.V = axis * sinf(angle / 2.0f);
		q.W = cosf(angle / 2.0f);
		return q;
	}

	Matrix4x4 GetMatrix()
	{
		Matrix4x4 result;
		result.M11 =    W; result.M21 = -V.Z; result.M31 = -V.Y; result.M41 =  V.X;
		result.M12 =  V.Z; result.M22 =    W; result.M32 = -V.X; result.M42 =  V.Y;
		result.M13 = -V.Y; result.M23 =  V.X; result.M33 =    W; result.M43 =  V.Z;
		result.M14 = -V.X; result.M24 = -V.Y; result.M34 = -V.Z; result.M44 =    W;
		return result;
	}

	Quaternion operator+(Quaternion other)
	{
		Quaternion result;
		result.W = W + other.W; result.V = V + other.V;
		return result;
	}

	Quaternion operator-(Quaternion other)
	{
		Quaternion result;
		result.W = W - other.W; result.V = V - other.V;
		return result;
	}

	Quaternion operator*(float scalar)
	{
		Quaternion result;
		result.W = W * scalar; result.V = V * scalar;
		return result;
	}

	Quaternion operator*(Quaternion other)
	{
		Quaternion result;
		result.W = W * other.W - Vector3::Dot(V, other.V);
		result.V = other.V * W + V * other.W + Vector3::Cross(V, other.V);
		return result;
	}
};