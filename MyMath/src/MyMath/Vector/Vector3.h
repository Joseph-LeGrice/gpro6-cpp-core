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

    static Vector3 One();
    static Vector3 Zero();
    
    static float Dot(const Vector3& a, const Vector3& b);
    static Vector3 Cross(const Vector3& a, const Vector3& b);
    static Vector3 Lerp(const Vector3& a, const Vector3& b, float time);

    Vector3() : X(0), Y(0), Z(0) { }
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) { }

    void Normalize();
    float Magnitude() const;

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
