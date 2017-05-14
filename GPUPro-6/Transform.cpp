#include "stdafx.h"
#include "Transform.h"


Transform::Transform()
{
	Matrix4x4::MatrixIdentity(&m_translation);
	Matrix4x4::MatrixIdentity(&m_scale);
	Matrix4x4::MatrixIdentity(&m_rotation);
}

Transform::~Transform()
{
}

void Transform::SetTranslation(Vector3 position)
{	
	m_translation.M41 = position.X;
	m_translation.M42 = position.Y;
	m_translation.M43 = position.Z;
}

void Transform::SetScale(Vector3 scale)
{
	m_scale.M11 = scale.X;
	m_scale.M22 = scale.Y;
	m_scale.M33 = scale.Z;
}

const Matrix4x4 Transform::GetTransformationMatrix()
{
	return m_translation * m_scale * m_rotation;
}
