#pragma once
#include "ConstantBuffer.h"

class VolumetricExplosionConstantBuffer : public ConstantBuffer
{
public:
	VolumetricExplosionConstantBuffer();
	~VolumetricExplosionConstantBuffer();

	virtual bool Initialize(ID3D11Device* device) override;
	virtual ID3D11Buffer* GetPSBuffer() override;

private:
	ID3D11Buffer* m_buffer;
};

