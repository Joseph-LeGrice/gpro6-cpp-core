#include "stdafx.h"

#include "Transform.h"
#include "Core/DataStructures\Matrix4x4.h"
#include "Core/DataStructures\Vector4.h"

Transform TransformNew()
{
	Transform t;
	t.m_scale = { 1.0f, 1.0f, 1.0f };
	t.m_position = { 0.0f, 0.0f, 0.0f };
	t.m_rotation = Quaternion::Identity();
	return t;
}

Vector3 Transform::WorldUp()
{
    Vector3 result = Vector3::Up() * m_rotation;
    Vector3::Normalize(result);
    return result;
}

Vector3 Transform::WorldRight()
{
    Vector3 result = Vector3::Right() * m_rotation;
    Vector3::Normalize(result);
    return result;
}

Vector3 Transform::WorldForward()
{
    Vector3 result = Vector3::Forward() * m_rotation;
    Vector3::Normalize(result);
    return result;
}

Matrix4x4 Transform::GetMatrix(const Transform& t)
{
	return Vector4::GetTranslationMatrix(Vector4::FromVector3(t.m_position)) *
		Vector4::GetScaleMatrix(Vector4::FromVector3(t.m_scale)) *
		Quaternion::GetMatrix(t.m_rotation);
}

Matrix4x4 Transform::GetCameraViewMatrix(const Transform& t)
{
    Matrix4x4 TR = Vector4::GetTranslationMatrix(Vector4::FromVector3(t.m_position)) *
        Quaternion::GetMatrix(t.m_rotation);
	return Matrix4x4::Inverse(TR);
}