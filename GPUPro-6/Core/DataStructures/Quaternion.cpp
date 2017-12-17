#include "stdafx.h"
#include "Core/Utilities/MathHelper.h"
#include "Core/DataStructures/Quaternion.h"

Quaternion Quaternion::Identity()
{
	Quaternion q;
	q.W = 1.0f;
	q.V = { 0.0, 0.0, 0.0 };
	return q;
}

Quaternion Quaternion::Conjugate(const Quaternion& q)
{
	Quaternion result;
	result.W = q.W;
	result.V = -q.V;
	return result;
}

Quaternion Quaternion::Inverse(const Quaternion& q)
{
	Quaternion con = Quaternion::Conjugate(q);
	float mag = Quaternion::Magnitude(q);

	Quaternion result;
	result.W = con.W / mag; result.V = con.V / mag;
	return result;
}

// TODO: Quaternion.LookAt

Quaternion Quaternion::FromAxisAngle(Vector3 axis, float angle)
{
	Quaternion q;
	q.W = cosf(angle / 2.0f);
	q.V = axis * sinf(angle / 2.0f);
	Quaternion::Normalize(q);
	return q;
}

Vector3 Quaternion::ToEuler(const Quaternion& q)
{
    Vector3 result;

    float sinr = 2 * (q.W * q.V.X + q.V.Y * q.V.Z);
    float cosr = 1 - 2 * (q.V.X * q.V.X + q.V.Y * q.V.Y);
    result.X = atan2f(sinr, cosr);

    float sinp = 2 * (q.W * q.V.Y - q.V.Z * q.V.X);
    if (abs(sinp) >= 1)
    {
        result.Y = copysign(PI / 2, sinp);
    }
    else
    {
        result.Y = asinf(sinp);
    }

    float siny = 2 * (q.W * q.V.Z + q.V.X * q.V.Y);
    float cosy = 1 - 2 * (q.V.Y * q.V.Y + q.V.Z * q.V.Z);
    result.Z = atan2f(siny, cosy);

    return result * RadToDeg;
}

Quaternion Quaternion::FromEuler(const Vector3& degrees)
{
    Vector3 radians = degrees * DegToRad;
    std::stringstream ss;
    ss << "radians: " << (std::string)radians;
    Log(ss.str());

    float cy = cosf(radians.Z * 0.5f);
    float sy = sinf(radians.Z * 0.5f);
    float cr = cosf(radians.X * 0.5f);
    float sr = sinf(radians.X * 0.5f);
    float cp = cosf(radians.Y * 0.5f);
    float sp = sinf(radians.Y * 0.5f);

    Quaternion q;
    q.W   = cy * cr * cp + sy * sr * sp;
    q.V.X = cy * sr * cp - sy * cr * sp;
    q.V.Y = cy * cr * sp + sy * sr * cp;
    q.V.Z = sy * cr * cp - cy * sr * sp;
    return q;
}

Quaternion Quaternion::FromLookRotation(Vector3 forward, Vector3 up)
{
    Vector3 right = Vector3::Cross(forward, up);
    Vector3 trueUp = Vector3::Cross(right, forward);
    Quaternion q;
    return q;
}

Matrix4x4 Quaternion::GetMatrix(const Quaternion& q)
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

void Quaternion::Normalize(Quaternion& q)
{
	FLOAT mag = Quaternion::Magnitude(q);
	q.W /= mag;
	q.V /= mag;
}

FLOAT Quaternion::Magnitude(const Quaternion& q)
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