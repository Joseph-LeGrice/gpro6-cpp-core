#include "stdafx.h"

#include "Components\Transform.h"
#include "DataStructures\Matrix4x4.h"
#include "DataStructures\Vector4.h"

Transform TransformNew()
{
	Transform t;
	t.m_scale = { 1.0f, 1.0f, 1.0f };
	t.m_position = { 0.0f, 0.0f, 0.0f };
	t.m_rotation = QuaternionIdentity();
	return t;
}

Matrix4x4 TransformGetMatrix(const Transform& t)
{
	return GetTranslationMatrix(Vector4FromVector3(t.m_position)) *
		GetScaleMatrix(Vector4FromVector3(t.m_scale)) *
		QuaternionGetMatrix(t.m_rotation);
}

Matrix4x4 TransformGetCameraViewMatrix(const Transform& t)
{
	return MatrixInverse(GetTranslationMatrix(Vector4FromVector3(t.m_position)));
}