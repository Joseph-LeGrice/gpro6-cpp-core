#pragma once
#include "D3DX11.h"
#include "D3DX10.h"
#include "Matrix4x4.h"


struct VS_CONSTANT_BUFFER
{
	Matrix4x4 MVP;
	Matrix4x4 WorldMatrix;
	Matrix4x4 ViewProjectionMatrix;
};

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	bool Initialize(ID3D11Device* device);
	void SetBuffers();
	void UpdateBuffers();
	void SetProjectionMatrix(Matrix4x4 vp);
	void SetViewMatrix(Matrix4x4 vp);
	void SetWorldMatrix(Matrix4x4 w);

private:
	Matrix4x4 m_vMatrix;
	Matrix4x4 m_pMatrix;
	Matrix4x4 m_wMatrix;
	ID3D11Buffer* m_buffer;

	VS_CONSTANT_BUFFER GetBufferData();
};

