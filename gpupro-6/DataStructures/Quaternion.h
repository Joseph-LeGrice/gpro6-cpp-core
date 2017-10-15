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

	static Quaternion Conjugate(const Quaternion& q)
	{
		Quaternion result;
		result.W = q.W;
		result.V = -result.V;
		return result;
	}

	static Quaternion Inverse(const Quaternion& q) 
	{
		Quaternion con = Quaternion::Conjugate(q);
		float mag = Quaternion::Magnitude(q);
		
		Quaternion result;
		result.W = con.W / mag; result.V = con.V / mag;
		return result;
	}

	// TODO: Quaternion.LookAt

	static Quaternion FromAxisAngle(Vector3 axis, float angle)
	{
		Quaternion q;
		q.W = cosf(angle / 2.0f);
		q.V = axis * sinf(angle / 2.0f);
		Quaternion::Normalize(q);
		return q;
	}

	static Matrix4x4 GetMatrix(const Quaternion& q)
	{
		//Orthonormal basis

		float x = q.V.X * 2.0F;
		float y = q.V.Y * 2.0F;
		float z = q.V.Z * 2.0F;
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

		result.M11 = 1.0f - (yy + zz); result.M21 = xy - wz;          result.M31 = xz + wy;          result.M41 = 0.0f;
		result.M12 = xy + wz;          result.M22 = 1.0f - (xx + zz); result.M32 = yz - wx;          result.M42 = 0.0f;
		result.M13 = xz - wy;          result.M23 = yz + wx;          result.M33 = 1.0f - (xx + yy); result.M43 = 0.0f;
		result.M14 = 0.0f;             result.M24 = 0.0f;             result.M34 = 0.0f;             result.M44 = 1.0f;
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
		result.V.X = W * other.V.X + V.X * other.W + V.Y * other.V.Z - V.Z * other.V.Y;
		result.V.Y = W * other.V.Y + V.Y * other.W + V.Z * other.V.X - V.X * other.V.Z;
		result.V.Z = W * other.V.Z + V.Z * other.W + V.X * other.V.Y - V.Y * other.V.X;
		result.W = W * other.W - V.X * other.V.X - V.Y * other.V.Y - V.Z * other.V.Z;
		return result;
	}

	void operator *=(const Quaternion& other)
	{
		Vector3 newV;
		newV.X = W * other.V.X + V.X * other.W + V.Y * other.V.Z - V.Z * other.V.Y;
		newV.Y = W * other.V.Y + V.Y * other.W + V.Z * other.V.X - V.X * other.V.Z;
		newV.Z = W * other.V.Z + V.Z * other.W + V.X * other.V.Y - V.Y * other.V.X;
		FLOAT newW = W * other.W - V.X * other.V.X - V.Y * other.V.Y - V.Z * other.V.Z;		
		W = newW; V = newV;
	}
};