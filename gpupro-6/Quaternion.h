#pragma once

#include <math.h>
#include "Vector3.h"

struct Quaternion
{
	FLOAT W;
	Vector3 V;

	static Quaternion Identity()
	{
		Quaternion q;
		q.W = 1.0f;
		q.V = { 0.0, 0.0, 0.0 };
		return q;
	}

	// TODO: Quaternion.LookAt

	static Quaternion FromAxisAngle(Vector3 axis, float angle)
	{
		Quaternion q;
		q.V = axis * sinf(angle / 2.0f);
		q.W = cosf(angle / 2.0f);
		Quaternion::Normalize(q);
		return q;
	}

	static Matrix4x4 GetMatrix(const Quaternion& q)
	{
		//Orthonormal basis

		float x  = q.V.X * 2.0F;
		float y  = q.V.Y * 2.0F;
		float z  = q.V.Z * 2.0F;
		float xx = q.V.X * x;
		float yy = q.V.Y * y;
		float zz = q.V.Z * z;
		float xy = q.V.X * y;
		float xz = q.V.X * z;
		float yz = q.V.Y * z;
		float wx = q.W * x;
		float wy = q.W * y;
		float wz = q.W * z;

		Matrix4x4 result;
		Matrix4x4::Identity(result);

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

	static void Normalize(Quaternion& q)
	{
		FLOAT mag = Magnitude(q);
		q.W /= mag;
		q.V /= mag;
	}

	static FLOAT Magnitude(const Quaternion& q)
	{
		return sqrt(pow(q.W, 2) + pow(q.V.X, 2) + pow(q.V.Y, 2) + pow(q.V.Z, 2));
	}

	Quaternion operator+(const Quaternion& other) const
	{
		Quaternion result;
		result.W = W + other.W; result.V = V + other.V;
		return result;
	}

	Quaternion operator-(const Quaternion& other) const
	{
		Quaternion result;
		result.W = W - other.W; result.V = V - other.V;
		return result;
	}

	Quaternion operator*(float scalar) const
	{
		Quaternion result;
		result.W = W * scalar; result.V = V * scalar;
		return result;
	}

	Quaternion operator*(const Quaternion& other) const
	{
		Quaternion result;
		result.W = W * other.W - Vector3::Dot(V, other.V);
		result.V = other.V * W + V * other.W + Vector3::Cross(V, other.V);
		return result;
	}

	void operator *=(const Quaternion& other)
	{
		W = W * other.W - Vector3::Dot(V, other.V);
		V = other.V * W + V * other.W + Vector3::Cross(V, other.V);
		Normalize(*this);
	}
};