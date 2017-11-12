#include "stdafx.h"

#include "Components\Transform.h"
#include "DataStructures\Matrix4x4.h"
#include "DataStructures\Vector4.h"

Transform TransformNew()
{
	Transform t;
	t.m_scale = { 1.0f, 1.0f, 1.0f };
	t.m_position = { 0.0f, 0.0f, 0.0f };
	t.m_rotation = Quaternion::Identity();
	return t;
}

Matrix4x4 Transform::GetMatrix(const Transform& t)
{
	return Vector4::GetTranslationMatrix(Vector4::FromVector3(t.m_position)) *
		Vector4::GetScaleMatrix(Vector4::FromVector3(t.m_scale)) *
		Quaternion::GetMatrix(t.m_rotation);
}

Matrix4x4 Transform::GetCameraViewMatrix(const Transform& t)
{
	return Matrix4x4::Inverse(Vector4::GetTranslationMatrix(Vector4::FromVector3(t.m_position)));
}