#pragma once

#include "DataStructures\Matrix4x4.h"
#include "DataStructures\Vector4.h"
#include "DataStructures\Quaternion.h"

struct Transform
{
	// TODO: Child / Parent functionality

	Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;

	static Transform New()
	{
		Transform t;
		t.m_scale = VectorOne();
		t.m_position = VectorZero();
		t.m_rotation = QuaternionIdentity();
		return t;
	}

	static void Free(Transform& t) { }

	static Matrix4x4 GetTransformationMatrix(const Transform& t)
	{
		return GetTranslationMatrix(Vector4FromVector3(t.m_position)) *
			GetScaleMatrix(Vector4FromVector3(t.m_scale)) *
			QuaternionGetMatrix(t.m_rotation);
	}

	static Matrix4x4 GetViewMatrix(const Transform& t)
	{
		return MatrixInverse(GetTranslationMatrix(Vector4FromVector3(t.m_position)));
	}
};