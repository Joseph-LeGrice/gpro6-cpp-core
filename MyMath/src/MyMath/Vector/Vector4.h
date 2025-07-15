#pragma once

#include "Vector3.h"

struct Matrix4x4;

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;

    static Vector4 FromVector3(const Vector3& v3);
    static Matrix4x4 GetTranslationMatrix(const Vector4& v);
    static Matrix4x4 GetScaleMatrix(const Vector4& v);
};
