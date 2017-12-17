#pragma once

#include <math.h>
#include "Core/Graphics/VertexData.h"
#include "Core/DataStructures/Matrix4x4.h"

struct Quaternion
{
	FLOAT W;
	Vector3 V;

    static Quaternion Identity();
    static Quaternion Conjugate(const Quaternion& q);
    static Quaternion Inverse(const Quaternion& q);
    static Quaternion FromAxisAngle(Vector3 axis, float angle);
    static Vector3 ToEuler(const Quaternion& q);
    static Quaternion FromEuler(const Vector3& v);
    static Quaternion FromLookRotation(Vector3 forward, Vector3 up = { 0, 1 ,0 });
    static Matrix4x4 GetMatrix(const Quaternion& q);
    static void Normalize(Quaternion& q);
    static FLOAT Magnitude(const Quaternion& q);

    operator std::string()
    {
        std::stringstream ss;
        ss << "{ " << V.X << ", " << V.Y << ", " << V.Z << ", " << W << " }";
        return ss.str();
    }
};

Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator*(const Quaternion& lhs, float rhs);
Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
void operator *=(Quaternion& lhs, const Quaternion& rhs);
