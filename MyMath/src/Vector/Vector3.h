#pragma once

#include <string>

struct Vector4;
struct Quaternion;

struct Vector3
{
	float X;
	float Y;
	float Z;

    static Vector3 Up();
    static Vector3 Right();
    static Vector3 Forward();

    static float Magnitude(Vector3& v);
    static void Normalize(Vector3& v);
    static float Dot(Vector3 a, Vector3 b);
    static Vector3 Cross(Vector3 a, Vector3 b);

    operator Vector4();
    operator std::string();
};

Vector3 operator+(const Vector3& first, const Vector3& second);
Vector3 operator-(const Vector3& rhs);
Vector3 operator-(const Vector3& rhs, const Vector3& second);
Vector3 operator*(const Vector3& first, const float factor);
Vector3 operator*(const float rhs, Vector3& lhs);
Vector3 operator*(const Vector3& lhs, const Quaternion& rhs);
Vector3 operator/(const Vector3& first, const float factor);

bool operator==(const Vector3& lhs, const Vector3& rhs);
bool operator!=(const Vector3& lhs, const Vector3& rhs);

void operator+=(Vector3& lhs, const Vector3& rhs);
void operator-=(Vector3& lhs, const Vector3& rhs);
void operator*=(Vector3& lhs, const Quaternion& rhs);
void operator*=(Vector3& lhs, const float rhs);
void operator/=(Vector3& lhs, const float rhs);
