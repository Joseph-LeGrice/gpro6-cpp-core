#pragma once

#include "Vector3.h"
#include "DataStructures\Matrix4x4.h"

struct Vector4
{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
	FLOAT W;
};

Vector4 Vector4FromVector3(const Vector3& v3);
Matrix4x4 GetTranslationMatrix(const Vector4& v);
Matrix4x4 GetScaleMatrix(const Vector4& v);