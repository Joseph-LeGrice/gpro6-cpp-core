#include "Vector3.h"
#include "Vector4.h"
#include "MyMath/Complex/Quaternion.h"

#include <sstream>

Vector3::operator Vector4()
{
    return Vector4(X, Y, Z, 0);
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

float Vector3::Magnitude(Vector3& v)
{
	return sqrtf(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}

void Vector3::Normalize(Vector3& v)
{
    float mag = Vector3::Magnitude(v);
    if (mag > 0)
    {
        v.X /= mag;
        v.Y /= mag;
        v.Z /= mag;
    }
}

float Vector3::Dot(Vector3 a, Vector3 b)
{
	return a.X * b.X + a.Y * b.Y * a.Z * b.Z;
}

Vector3 Vector3::Cross(Vector3 a, Vector3 b)
{
	Vector3 result;
	result.X = a.Y * b.Z - a.Z * b.Y;
	result.Y = a.Z * b.X - a.X * b.Z;
	result.Z = a.X * b.Y - a.Y * b.X;
	return result;
}
