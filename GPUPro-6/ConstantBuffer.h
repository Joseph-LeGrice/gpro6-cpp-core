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
	void SetBuffers();
	void UpdateBuffers();
	void ConstantBuffer::SetViewProjectionMatrix(Matrix4x4 vp);
	void ConstantBuffer::SetWorldMatrix(Matrix4x4 w);

private:
	Matrix4x4 m_vpMatrix;
	Matrix4x4 m_wMatrix;
	ID3D11Buffer* m_buffer;

	VS_CONSTANT_BUFFER GetBufferData();
};

