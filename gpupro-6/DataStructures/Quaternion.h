#pragma once

#include <math.h>
#include "DataStructures/VertexData.h"
#include "DataStructures/Matrix4x4.h"

struct Quaternion
{
	FLOAT W;
	Vector3 V;
};

Quaternion QuaternionIdentity();
Quaternion QuaternionConjugate(const Quaternion& q);
Quaternion QuaternionInverse(const Quaternion& q);
// TODO: QuaternionLookAt
Quaternion QuaternionFromAxisAngle(Vector3 axis, float angle);
Matrix4x4 QuaternionGetMatrix(const Quaternion& q);
void QuaternionNormalize(Quaternion& q);
FLOAT QuaternionMagnitude(const Quaternion& q);
Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator*(const Quaternion& lhs, float rhs);
Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
void operator *=(Quaternion& lhs, const Quaternion& rhs);