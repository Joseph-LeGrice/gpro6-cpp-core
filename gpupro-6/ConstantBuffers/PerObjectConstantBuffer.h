#pragma once
#include "ConstantBuffer.h"

#include "D3DX11.h"
#include "D3DX10.h"
#include "Matrix4x4.h"


struct VS_CONSTANT_BUFFER
{
	Matrix4x4 ModelViewProjection;
	Matrix4x4 ModelView;
};

class PerObjectConstantBuffer : public ConstantBuffer
{
public:
	PerObjectConstantBuffer();
	virtual ~PerObjectConstantBuffer() override;

	virtual bool Initialize(ID3D11Device* device) override;
	virtual	void SetBuffers() override;
	virtual	void UpdateBuffers() override;

	void SetProjectionMatrix(const Matrix4x4& vp);
	void SetViewMatrix(const Matrix4x4& vp);
	void SetWorldMatrix(const Matrix4x4& w);

protected:
private:
	Matrix4x4 m_vMatrix;
	Matrix4x4 m_pMatrix;
	Matrix4x4 m_wMatrix;
	ID3D11Buffer* m_buffer;

	VS_CONSTANT_BUFFER GetBufferData();
};
