#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include "D3D10.h"

struct Vector4
{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
	FLOAT W;

	static Vector4 FromVector3(Vector3& v3)
	{
		Vector4 v4;
		v4.X = v3.X;
		v4.Y = v3.Y;
		v4.Z = v3.Z;
		v4.W = 1.0f;
		return v4;
	}

	static Matrix4x4 GetTranslationMatrix(Vector4& v)
	{
		Matrix4x4 translation;
		translation.M41 = v.X;
		translation.M42 = v.Y;
		translation.M43 = v.Z;
		translation.M44 = v.W;
		return translation;
	}

	static Matrix4x4 GetScaleMatrix(Vector4& v)
	{
		Matrix4x4 scale;
		scale.M11 = v.X;
		scale.M22 = v.Y;
		scale.M33 = v.Z;
		scale.M44 = v.W;
		return scale;
	}
};