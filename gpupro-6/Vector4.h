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

	Vector4()
	{

	}

	Vector4(Vector3 v3)
	{
		X = v3.X;
		Y = v3.Y;
		Z = v3.Z;
		W = 1.0f;
	}

	Matrix4x4 GetTranslationMatrix()
	{
		Matrix4x4 translation;
		translation.M41 = X;
		translation.M42 = Y;
		translation.M43 = Z;
		translation.M44 = W;
		return translation;
	}

	Matrix4x4 GetScaleMatrix()
	{
		Matrix4x4 scale;
		scale.M11 = X;
		scale.M22 = Y;
		scale.M33 = Z;
		scale.M44 = W;
		return scale;
	}
};