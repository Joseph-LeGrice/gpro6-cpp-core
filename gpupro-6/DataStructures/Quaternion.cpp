#include "stdafx.h"
#include "DataStructures/Quaternion.h"

Quaternion QuaternionIdentity()
{
	Quaternion q;
	q.W = 1.0f;
	q.V = { 0.0, 0.0, 0.0 };
	return q;
}

Quaternion QuaternionConjugate(const Quaternion& q)
{
	Quaternion result;
	result.W = q.W;
	result.V = -result.V;
	return result;
}

Quaternion QuaternionInverse(const Quaternion& q)
{
	Quaternion con = QuaternionConjugate(q);
	float mag = QuaternionMagnitude(q);

	Quaternion result;
	result.W = con.W / mag; result.V = con.V / mag;
	return result;
}

// TODO: Quaternion.LookAt

Quaternion QuaternionFromAxisAngle(Vector3 axis, float angle)
{
	Quaternion q;
	q.W = cosf(angle / 2.0f);
	q.V = axis * sinf(angle / 2.0f);
	QuaternionNormalize(q);
	return q;
}

Matrix4x4 QuaternionGetMatrix(const Quaternion& q)
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
	MatrixIdentity(result);

	result.M11 = 1.0f - (yy + zz); result.M21 = xy - wz;          result.M31 = xz + wy;          result.M41 = 0.0f;
	result.M12 = xy + wz;          result.M22 = 1.0f - (xx + zz); result.M32 = yz - wx;          result.M42 = 0.0f;
	result.M13 = xz - wy;          result.M23 = yz + wx;          result.M33 = 1.0f - (xx + yy); result.M43 = 0.0f;
	result.M14 = 0.0f;             result.M24 = 0.0f;             result.M34 = 0.0f;             result.M44 = 1.0f;
	return result;
}

void QuaternionNormalize(Quaternion& q)
{
	FLOAT mag = QuaternionMagnitude(q);
	q.W /= mag;
	q.V /= mag;
}

FLOAT QuaternionMagnitude(const Quaternion& q)
{
	return sqrt(pow(q.W, 2) + pow(q.V.X, 2) + pow(q.V.Y, 2) + pow(q.V.Z, 2));
}

Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;
	result.W = lhs.W + rhs.W; result.V = lhs.V + rhs.V;
	return result;
}

Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;
	result.W = lhs.W - rhs.W; result.V = lhs.V - rhs.V;
	return result;
}

Quaternion operator*(const Quaternion& lhs, float rhs)
{
	Quaternion result;
	result.W = lhs.W * rhs; result.V = lhs.V * rhs;
	return result;
}

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;
	result.V.X = lhs.W * rhs.V.X + lhs.V.X * rhs.W + lhs.V.Y * rhs.V.Z - lhs.V.Z * rhs.V.Y;
	result.V.Y = lhs.W * rhs.V.Y + lhs.V.Y * rhs.W + lhs.V.Z * rhs.V.X - lhs.V.X * rhs.V.Z;
	result.V.Z = lhs.W * rhs.V.Z + lhs.V.Z * rhs.W + lhs.V.X * rhs.V.Y - lhs.V.Y * rhs.V.X;
	result.W = lhs.W * rhs.W - lhs.V.X * rhs.V.X - lhs.V.Y * rhs.V.Y - lhs.V.Z * rhs.V.Z;
	return result;
}

void operator *=(Quaternion& lhs, const Quaternion& rhs)
{
	Vector3 newV;
	newV.X = lhs.W * rhs.V.X + lhs.V.X * rhs.W + lhs.V.Y * rhs.V.Z - lhs.V.Z * rhs.V.Y;
	newV.Y = lhs.W * rhs.V.Y + lhs.V.Y * rhs.W + lhs.V.Z * rhs.V.X - lhs.V.X * rhs.V.Z;
	newV.Z = lhs.W * rhs.V.Z + lhs.V.Z * rhs.W + lhs.V.X * rhs.V.Y - lhs.V.Y * rhs.V.X;
	FLOAT newW = lhs.W * rhs.W - lhs.V.X * rhs.V.X - lhs.V.Y * rhs.V.Y - lhs.V.Z * rhs.V.Z;
	lhs.W = newW; lhs.V = newV;
}