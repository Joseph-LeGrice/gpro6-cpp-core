#pragma once

#include <string>

struct Matrix4x4;
struct Vector3;

struct Quaternion
{
	float W;
    float X;
    float Y;
    float Z;

    static Quaternion Identity();
    static Quaternion Conjugate(const Quaternion& q);
    static Quaternion Inverse(const Quaternion& q);
    static Quaternion FromAxisAngle(Vector3 axis, float angle);
    static Vector3 ToEuler(const Quaternion& q);
    static Quaternion FromEuler(const Vector3& v);
    static Quaternion FromLookRotation(const Vector3& forward);
    static Quaternion FromLookRotation(const Vector3& forward, const Vector3& up);
    static Matrix4x4 GetMatrix(const Quaternion& q);
    static void Normalize(Quaternion& q);
    static float Magnitude(const Quaternion& q);

    operator std::string();
};

Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator*(const Quaternion& lhs, float rhs);
Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
void operator *=(Quaternion& lhs, const Quaternion& rhs);
