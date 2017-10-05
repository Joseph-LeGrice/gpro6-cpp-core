#pragma once
#include "D3DX11.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	virtual ~ConstantBuffer();

	virtual bool Initialize(ID3D11Device* device) = 0;
	virtual void SetBuffers() = 0;
	virtual void UpdateBuffers() = 0;
};

