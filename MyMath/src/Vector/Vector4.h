#pragma once

#include "Vector3.h"

struct Matrix4x4;

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;

    Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) { }
    Vector4() : Vector4(0, 0, 0, 0) {}

    static Vector4 FromVector3(const Vector3& v3);
    static Matrix4x4 GetTranslationMatrix(const Vector4& v);
    static Matrix4x4 GetScaleMatrix(const Vector4& v);
};
