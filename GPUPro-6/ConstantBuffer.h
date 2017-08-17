#pragma once
#include "D3DX11.h"
#include "D3DX10.h"
#include "Matrix.h"

typedef struct VS_CONSTANT_BUFFER;

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	bool Initialize(ID3D11Device* device);
	void SetModelViewProjectionMatrix(Matrix4x4 mvp, ID3D11DeviceContext* context);
	ID3D11Buffer* GetVSBuffer();
	ID3D11Buffer* GetHSBuffer();
	ID3D11Buffer* GetDSBuffer();
	ID3D11Buffer* GetGSBuffer();
	ID3D11Buffer* GetPSBuffer();


private:
	ID3D11Buffer* m_buffer;
	VS_CONSTANT_BUFFER GetBufferData(Matrix4x4 transform);
};

