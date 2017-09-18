#pragma once

#include <math.h>
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

	// TODO: Quaternion.LookAt

	static Quaternion FromAxisAngle(Vector3 axis, float angle)
	{
		Quaternion q;
		q.V = axis * sinf(angle / 2.0f);
		q.W = cosf(angle / 2.0f);
		q.Normalize();
		return q;
	}

	Matrix4x4 GetMatrix()
	{
		//Orthonormal basis

		float x = V.X * 2.0F;
		float y = V.Y * 2.0F;
		float z = V.Z * 2.0F;
		float xx = V.X * x;
		float yy = V.Y * y;
		float zz = V.Z * z;
		float xy = V.X * y;
		float xz = V.X * z;
		float yz = V.Y * z;
		float wx = W * x;
		float wy = W * y;
		float wz = W * z;

		Matrix4x4 result; 
		result.M11 = 1.0f - (yy + zz);
		result.M12 = xy + wz;
		result.M13 = xz - wy;
		result.M14 = 0.0F;

		result.M21 = xy - wz;
		result.M22 = 1.0f - (xx + zz);
		result.M23 = yz + wx;
		result.M24 = 0.0F;

		result.M31 = xz + wy;
		result.M32 = yz - wx;
		result.M33 = 1.0f - (xx + yy);
		result.M34 = 0.0F;
		
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
		return result;
	}

	void Normalize()
	{
		FLOAT mag = Magnitude();
		W /= mag;
		V /= mag;
	}

	FLOAT Magnitude()
	{
		return sqrt(pow(W, 2) + pow(V.X, 2) + pow(V.Y, 2) + pow(V.Z, 2));
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