#include "Quaternion.h"
#include "MyMath/MathDefines.h"

#include "MyMath/Assertions_Math.h"
#include "MyMath/Matrix/Matrix4x4.h"
#include "MyMath/Vector/Vector3.h"

#include <math.h>
#include <sstream>

Quaternion Quaternion::Identity()
{
	Quaternion q;
	q.W = 1.0f;
    q.X = 0.0f;
    q.Y = 0.0f;
    q.Z = 0.0f;
	return q;
}

Quaternion Quaternion::Conjugate(const Quaternion& q)
{
	Quaternion result;
	result.W = q.W;
    result.X = -q.X;
    result.Y = -q.Y;
    result.Z = -q.Z;
	return result;
}

Quaternion Quaternion::Inverse(const Quaternion& q)
{
	Quaternion con = Quaternion::Conjugate(q);
	float mag = Quaternion::Magnitude(q);

	Quaternion result;
	result.W = con.W / mag; 
    result.X = con.X / mag;
    result.Y = con.Y / mag;
    result.Z = con.Z / mag;
	return result;
}

Quaternion Quaternion::FromAxisAngle(Vector3 axis, float angle)
{
	Quaternion q;
	q.W = cosf(angle / 2.0f);

	Vector3 vectorComponent = axis * sinf(angle / 2.0f);
    q.X = vectorComponent.X;
    q.Y = vectorComponent.Y;
    q.Z = vectorComponent.Z;

	Quaternion::Normalize(q);
	return q;
}

Vector3 Quaternion::ToEuler(const Quaternion& q)
{
    Vector3 result;

    float sinr = 2.0f * (q.W * q.X + q.Y * q.Z);
    float cosr = 1.0f - 2.0f * (q.X * q.X + q.Y * q.Y);
    result.X = atan2f(sinr, cosr);

    float sinp = 2.0f * (q.W * q.Y - q.Z * q.X);
    if (abs(sinp) >= 1.0f)
    {
        result.Y = copysign(MyMath::PI / 2.0f, sinp);
    }
    else
    {
        result.Y = asinf(sinp);
    }

    float siny = 2.0f * (q.W * q.Z + q.X * q.Y);
    float cosy = 1.0f - 2.0f * (q.Y * q.Y + q.Z * q.Z);
    result.Z = atan2f(siny, cosy);

    return result * MyMath::RadToDeg;
}

Quaternion Quaternion::FromEuler(const Vector3& v)
{
    return Quaternion::FromEuler(v.X, v.Y, v.Z);
}

Quaternion Quaternion::FromEuler(float pitchDegrees, float yawDegrees, float rollDegrees)
{
    float pitchRadians = pitchDegrees * MyMath::DegToRad;
    float yawRadians = yawDegrees * MyMath::DegToRad;
    float rollRadians = rollDegrees * MyMath::DegToRad;

    float cy = cosf(rollRadians * 0.5f);
    float sy = sinf(rollRadians * 0.5f);
    float cr = cosf(pitchRadians * 0.5f);
    float sr = sinf(pitchRadians * 0.5f);
    float cp = cosf(yawRadians * 0.5f);
    float sp = sinf(yawRadians * 0.5f);

    Quaternion q;
    q.W   = cy * cr * cp + sy * sr * sp;
    q.X = cy * sr * cp - sy * cr * sp;
    q.Y = cy * cr * sp + sy * sr * cp;
    q.Z = sy * cr * cp - cy * sr * sp;

    Quaternion::Normalize(q);

    return q;
}

Quaternion Quaternion::FromLookRotation(const Vector3& forward, const Vector3& up)
{
    custom_assert::not_equal(forward, up);

    Vector3 right = Vector3::Cross(up, forward);
    Vector3 trueUp = Vector3::Cross(forward, right);
    right.Normalize();
    trueUp.Normalize();

    float m00 = right.X;
    float m01 = trueUp.X;
    float m02 = forward.X;
    float m10 = right.Y;
    float m11 = trueUp.Y;
    float m12 = forward.Y;
    float m20 = right.Z;
    float m21 = trueUp.Z;
    float m22 = forward.Z;

    Quaternion q;
    
    float tr = m00 + m11 + m22;
    if (tr > 0)
    {
        float S = sqrtf(tr + 1.0f) * 2.0f;
        q.W = 0.25f * S;
        q.X = (m21 - m12) / S;
        q.Y = (m02 - m20) / S;
        q.Z = (m10 - m01) / S;
    }
    else if ((m00 > m11) && (m00 > m22))
    {
        float S = sqrt(1.0f + m00 - m11 - m22) * 2;
        q.W = (m21 - m12) / S;
        q.X = 0.25f * S;
        q.Y = (m01 + m10) / S;
        q.Z = (m02 + m20) / S;
    }
    else if (m11 > m22)
    {
        float S = sqrt(1.0f + m11 - m00 - m22) * 2;
        q.W = (m02 - m20) / S;
        q.X = (m01 + m10) / S;
        q.Y = 0.25f * S;
        q.Z = (m12 + m21) / S;
    }
    else
    {
        float S = sqrt(1.0f + m22 - m00 - m11) * 2;
        q.W = (m10 - m01) / S;
        q.X = (m02 + m20) / S;
        q.Y = (m12 + m21) / S;
        q.Z = 0.25f * S;
    }

    Quaternion::Normalize(q);
    custom_assert::not_inf(q);
    custom_assert::not_nan(q);

    return q;
}

Quaternion Quaternion::FromLookRotation(const Vector3& forward)
{
    return FromLookRotation(forward, { 0, 1, 0 });
}

Matrix4x4 Quaternion::GetMatrix(const Quaternion& q)
{
	//Orthonormal basis

	float x = q.X * 2.0F;
	float y = q.Y * 2.0F;
	float z = q.Z * 2.0F;
	float xx = q.X * x;
	float yy = q.Y * y;
	float zz = q.Z * z;
	float xy = q.X * y;
	float xz = q.X * z;
	float yz = q.Y * z;
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
	float mag = Quaternion::Magnitude(q);
	q.W /= mag;
    q.X /= mag;
    q.Y /= mag;
    q.Z /= mag;
}

float Quaternion::Magnitude(const Quaternion& q)
{
	return sqrt(pow(q.W, 2) + pow(q.X, 2) + pow(q.Y, 2) + pow(q.Z, 2));
}

Quaternion::operator std::string()
{
    std::stringstream ss;
    ss << "{ " << W << ", " << X << ", " << Y << ", " << Z << " }";
    return ss.str();
}

Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;
	result.W = lhs.W + rhs.W; 
    result.X = lhs.X + rhs.X;
    result.Y = lhs.Y + rhs.Y;
    result.Z = lhs.Z + rhs.Z;
	return result;
}

Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;
	result.W = lhs.W - rhs.W; 
    result.X = lhs.X - rhs.X;
    result.Y = lhs.Y - rhs.Y;
    result.Z = lhs.Z - rhs.Z;
	return result;
}

Quaternion operator*(const Quaternion& lhs, float rhs)
{
	Quaternion result;
	result.W = lhs.W * rhs;
    result.X = lhs.X * rhs;
    result.Y = lhs.Y * rhs;
    result.Z = lhs.Z * rhs;
	return result;
}

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;
	result.X = lhs.W * rhs.X + lhs.X * rhs.W + lhs.Y * rhs.Z - lhs.Z * rhs.Y;
	result.Y = lhs.W * rhs.Y + lhs.Y * rhs.W + lhs.Z * rhs.X - lhs.X * rhs.Z;
	result.Z = lhs.W * rhs.Z + lhs.Z * rhs.W + lhs.X * rhs.Y - lhs.Y * rhs.X;
	result.W = lhs.W * rhs.W - lhs.X * rhs.X - lhs.Y * rhs.Y - lhs.Z * rhs.Z;
	return result;
}

void operator *=(Quaternion& lhs, const Quaternion& rhs)
{
	Vector3 newV;
	newV.X = lhs.W * rhs.X + lhs.X * rhs.W + lhs.Y * rhs.Z - lhs.Z * rhs.Y;
	newV.Y = lhs.W * rhs.Y + lhs.Y * rhs.W + lhs.Z * rhs.X - lhs.X * rhs.Z;
	newV.Z = lhs.W * rhs.Z + lhs.Z * rhs.W + lhs.X * rhs.Y - lhs.Y * rhs.X;
	float newW = lhs.W * rhs.W - lhs.X * rhs.X - lhs.Y * rhs.Y - lhs.Z * rhs.Z;
	
    lhs.W = newW;
    lhs.X = newV.X;
    lhs.Y = newV.Y;
    lhs.Z = newV.Z;
}
