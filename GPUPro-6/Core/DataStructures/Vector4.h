#pragma once

#include "Vector3.h"
#include "Core/DataStructures\Matrix4x4.h"

struct Vector4
{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
	FLOAT W;

    Vector4(FLOAT x, FLOAT y, FLOAT z, FLOAT w) : X(x), Y(y), Z(z), W(w) { }
    Vector4() : Vector4(0, 0, 0, 0) {}

    static Vector4 FromVector3(const Vector3& v3);
    static Matrix4x4 GetTranslationMatrix(const Vector4& v);
    static Matrix4x4 GetScaleMatrix(const Vector4& v);
};
