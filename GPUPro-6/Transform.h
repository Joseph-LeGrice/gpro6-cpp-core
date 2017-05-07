#pragma once
#include "D3DX11.h"
#include "D3DX10.h"

class Transform
{
public:
	Transform();
	~Transform();

	const D3DXMATRIX GetTransformationMatrix();

private:
	D3DXMATRIX m_scale;
	D3DXMATRIX m_rotation;
	D3DXMATRIX m_translation;
};

