#pragma once

#include <math.h>
#include "Graphics/VertexData.h"
#include "DataStructures/Matrix4x4.h"

struct Quaternion
{
	FLOAT W;
	Vector3 V;

    static Quaternion Identity();
    static Quaternion Conjugate(const Quaternion& q);
    static Quaternion Inverse(const Quaternion& q);
    static Quaternion FromAxisAngle(Vector3 axis, float angle);
    static Matrix4x4 GetMatrix(const Quaternion& q);
    static void Normalize(Quaternion& q);
    static FLOAT Magnitude(const Quaternion& q);
};

Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator*(const Quaternion& lhs, float rhs);
Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
void operator *=(Quaternion& lhs, const Quaternion& rhs);