#pragma once
#include "D3DX11.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	virtual bool Initialize(ID3D11Device* device) = 0;
	virtual ID3D11Buffer* GetVSBuffer();
	virtual ID3D11Buffer* GetHSBuffer();
	virtual ID3D11Buffer* GetDSBuffer();
	virtual ID3D11Buffer* GetGSBuffer();
	virtual ID3D11Buffer* GetPSBuffer();
};

