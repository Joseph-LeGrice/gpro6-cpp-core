#include "stdafx.h"
#include "DataStructures/Vector4.h"

Vector4 Vector4::FromVector3(const Vector3& v3)
{
	Vector4 v4;
	v4.X = v3.X;
	v4.Y = v3.Y;
	v4.Z = v3.Z;
	v4.W = 1.0f;
	return v4;
}

Matrix4x4 Vector4::GetTranslationMatrix(const Vector4& v)
{
	Matrix4x4 translation;
    Matrix4x4::Identity(translation);
	translation.M41 = v.X;
	translation.M42 = v.Y;
	translation.M43 = v.Z;
	translation.M44 = v.W;
	return translation;
}

Matrix4x4 Vector4::GetScaleMatrix(const Vector4& v)
{
	Matrix4x4 scale;
	Matrix4x4::Identity(scale);
	scale.M11 = v.X;
	scale.M22 = v.Y;
	scale.M33 = v.Z;
	scale.M44 = v.W;
	return scale;
}