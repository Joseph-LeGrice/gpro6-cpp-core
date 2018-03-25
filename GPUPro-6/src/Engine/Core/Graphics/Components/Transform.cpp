#include "stdafx.h"

#include "Transform.h"
#include "MyMath/Matrix/Matrix4x4.h"
#include "MyMath/Vector/Vector4.h"

void Transform::SetPosition(Vector3 position)
{
    custom_assert::not_nan(position);
    custom_assert::not_inf(position);

    m_position = position;
}

void Transform::SetScale(Vector3 scale)
{
    custom_assert::not_nan(scale);
    custom_assert::not_inf(scale);

    m_scale = scale;
}

void Transform::SetRotation(Quaternion rotation)
{
    custom_assert::not_nan(rotation);
    custom_assert::not_inf(rotation);

    m_rotation = rotation;
}

Vector3 Transform::WorldUp()
{
    Vector3 result = Vector3::Up() * m_rotation;
    result.Normalize();
    return result;
}

Vector3 Transform::WorldRight()
{
    Vector3 result = Vector3::Right() * m_rotation;
    result.Normalize();
    return result;
}

Vector3 Transform::WorldForward()
{
    Vector3 result = Vector3::Forward() * m_rotation;
    result.Normalize();
    return result;
}

Matrix4x4 Transform::GetMatrix()
{
	return Vector4::GetTranslationMatrix(Vector4::FromVector3(m_position)) *
		Vector4::GetScaleMatrix(Vector4::FromVector3(m_scale)) *
		Quaternion::GetMatrix(m_rotation);
}

Matrix4x4 Transform::GetCameraViewMatrix()
{
    Matrix4x4 TR = Vector4::GetTranslationMatrix(Vector4::FromVector3(m_position)) *
        Quaternion::GetMatrix(m_rotation);
	return Matrix4x4::Inverse(TR);
}