#pragma once

struct Vector3
{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;

    FLOAT Magnitude(Vector3& v);
    void Normalize(Vector3& v);
    FLOAT Dot(Vector3 a, Vector3 b);
    Vector3 Cross(Vector3 a, Vector3 b);
};

Vector3 operator+(const Vector3& first, const Vector3& second);
Vector3 operator-(const Vector3& rhs);
Vector3 operator-(const Vector3& rhs, const Vector3& second);
Vector3 operator*(const Vector3& first, const float factor);
Vector3 operator*(const float rhs, Vector3& lhs);
Vector3 operator/(const Vector3& first, const float factor);
void operator+=(Vector3& lhs, const Vector3& rhs);
void operator-=(Vector3& lhs, const Vector3& rhs);
void operator*=(Vector3& lhs, const float rhs);
void operator/=(Vector3& lhs, const float rhs);
