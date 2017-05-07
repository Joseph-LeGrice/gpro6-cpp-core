#include "stdafx.h"
#include "Transform.h"


Transform::Transform()
{
	D3DXMatrixTranslation(&m_translation, 0.0f, 0.0f, 0.0f);
	D3DXMatrixRotationYawPitchRoll(&m_rotation, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&m_scale, 1.0f, 1.5f, 1.0f);

	//D3DXMatrixIdentity(&m_translation);
	//D3DXMatrixIdentity(&m_rotation);
	//D3DXMatrixIdentity(&m_scale);
}

Transform::~Transform()
{
}

const D3DXMATRIX Transform::GetTransformationMatrix()
{
	return m_rotation * m_scale * m_translation;
}
