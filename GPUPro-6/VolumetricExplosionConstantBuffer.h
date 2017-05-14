#pragma once
#include "ConstantBuffer.h"

typedef struct VS_CONSTANT_BUFFER;

class VolumetricExplosionConstantBuffer : public ConstantBuffer
{
public:
	VolumetricExplosionConstantBuffer();
	~VolumetricExplosionConstantBuffer();

	virtual bool Initialize(ID3D11Device* device) override;
	virtual ID3D11Buffer* GetVSBuffer() override;
	virtual ID3D11Buffer* GetHSBuffer() override;
	virtual ID3D11Buffer* GetDSBuffer() override;
	virtual ID3D11Buffer* GetGSBuffer() override;
	virtual ID3D11Buffer* GetPSBuffer() override;
	virtual void SetModelViewProjectionMatrix(Matrix4x4 mvp, ID3D11DeviceContext* context) override;

private:
	ID3D11Buffer* m_buffer;
	VS_CONSTANT_BUFFER GetBufferData(Matrix4x4 transform);
};

