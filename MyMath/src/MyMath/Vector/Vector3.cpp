#include "Vector3.h"
#include "Vector4.h"
#include "MyMath/Complex/Quaternion.h"
#include "MyMath/MathDefines.h"

#include <sstream>

Vector3::operator Vector4()
{
	Vector4 v;
	v.X = X;
	v.Y = Y;
	v.Z = Z;
	v.W = 0;
	return v;
}

Vector3::operator std::string()
{
    std::stringstream ss;
    ss << "{ " << X << ", " << Y << ", " << Z << " }";
    return ss.str();
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 result;
	result.X = lhs.X + rhs.X; result.Y = lhs.Y + rhs.Y; result.Z = lhs.Z + rhs.Z;
	return result;
}

Vector3 operator-(const Vector3& rhs)
{
	Vector3 result;
	result.X = -rhs.X; result.Y = -rhs.Y; result.Z = -rhs.Z;
	return result;
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 result;
	result.X = lhs.X - rhs.X; result.Y = lhs.Y - rhs.Y; result.Z = lhs.Z - rhs.Z;
	return result;
}

Vector3 operator*(const Vector3& lhs, const float rhs)
{
	Vector3 result;
	result.X = lhs.X * rhs; result.Y = lhs.Y * rhs; result.Z = lhs.Z * rhs;
	return result;
}

Vector3 operator*(const float lhs, Vector3& rhs)
{
	Vector3 result;
	result.X = rhs.X * lhs; result.Y = rhs.Y * lhs; result.Z = rhs.Z * lhs;
	return result;
}

Vector3 operator*(const Vector3& lhs, const Quaternion& rhs)
{
    Quaternion pureComponent = { 0, lhs.X, lhs.Y, lhs.Z };
    Quaternion conjugate = Quaternion::Conjugate(rhs);
    Quaternion pureResult = (rhs * pureComponent) * conjugate;
    return { pureResult.X, pureResult.Y, pureResult.Z };
}

Vector3 operator/(const Vector3& first, const float factor)
{
	Vector3 result;
	result.X = first.X / factor; result.Y = first.Y / factor; result.Z = first.Z / factor;
	return result;
}

bool operator!=(const Vector3& lhs, const Vector3& rhs)
{
    return lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z;
}

bool operator==(const Vector3& lhs, const Vector3& rhs)
{
    return lhs.X != rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
}

void operator*=(Vector3& lhs, const Quaternion& rhs)
{
    Quaternion pureComponent = { 0, lhs.X, lhs.Y, lhs.Z };
    Quaternion conjugate = Quaternion::Conjugate(rhs);
    Quaternion pureResult = (rhs * pureComponent) * conjugate;
    lhs = { pureResult.X, pureResult.Y, pureResult.Z };
}

void operator+=(Vector3& lhs, const Vector3& rhs) { lhs.X += rhs.X; lhs.Y += rhs.Y; lhs.Z += rhs.Z; }
void operator-=(Vector3& lhs, const Vector3& rhs) { lhs.X -= rhs.X; lhs.Y -= rhs.Y; lhs.Z -= rhs.Z; }
void operator*=(Vector3& lhs, const float rhs) { lhs.X *= rhs; lhs.Y *= rhs; lhs.Z *= rhs; }
void operator/=(Vector3& lhs, const float rhs) { lhs.X /= rhs; lhs.Y /= rhs; lhs.Z /= rhs; }

Vector3 Vector3::Up()
{
    return { 0, 1, 0 };
}

Vector3 Vector3::Right()
{
    return { 1, 0, 0 };
}

Vector3 Vector3::Forward()
{
    return { 0, 0, 1 };
}

Vector3 Vector3::One()
{
    return{ 1, 1, 1 };
}

Vector3 Vector3::Zero()
{
    return{ 0, 0, 0 };
}
float Vector3::Magnitude() const
{
	return sqrtf(X * X + Y * Y + Z * Z);
}

void Vector3::Normalize()
{
    float mag = Magnitude();
    if (mag > 0)
    {
        X /= mag;
        Y /= mag;
        Z /= mag;
    }
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return a.X * b.X + a.Y * b.Y * a.Z * b.Z;
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
	Vector3 result;
	result.X = a.Y * b.Z - a.Z * b.Y;
	result.Y = a.Z * b.X - a.X * b.Z;
	result.Z = a.X * b.Y - a.Y * b.X;
	return result;
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float time)
{
    time = MyMath::Clamp01(time);
    Vector3 offset = b - a;
    offset.Normalize();
    return a + offset * time;
}
