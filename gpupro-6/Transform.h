#pragma once

#include "Matrix4x4.h"
#include "Vector4.h"
#include "Quaternion.h"

struct Transform
{
	// TODO: Child / Parent functionality

	Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;

	static Transform New()
	{
		Transform t;
		t.m_scale = Vector3::One();
		t.m_position = Vector3::Zero();
		t.m_rotation = Quaternion::Identity();
		return t;
	}

	static void Free(Transform& t) { }

	static Matrix4x4 GetTransformationMatrix(Transform& t)
	{
		return Vector4::GetTranslationMatrix(Vector4::FromVector3(t.m_position)) *
			Vector4::GetScaleMatrix(Vector4::FromVector3(t.m_scale)) *
			Quaternion::GetMatrix(t.m_rotation);
	}

	static Matrix4x4 GetViewMatrix(Transform& t)
	{
		return Matrix4x4::Inverse(Vector4::GetTranslationMatrix(Vector4::FromVector3(t.m_position)));
	}
};