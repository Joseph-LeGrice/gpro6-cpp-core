#include "stdafx.h"
#include "glm/glm.hpp"
#include "VolumetricExplosionConstantBuffer.h"


VolumetricExplosionConstantBuffer::VolumetricExplosionConstantBuffer()
{
	m_buffer = nullptr;
}


VolumetricExplosionConstantBuffer::~VolumetricExplosionConstantBuffer()
{
}

bool VolumetricExplosionConstantBuffer::Initialize(ID3D11Device* device)
{
	struct VS_CONSTANT_BUFFER
	{
		float time;
		float NoiseScale;
		float NoiseAmplitudeFactor;
		float NoiseFrequencyFactor;
	};

	VS_CONSTANT_BUFFER initialData;
	initialData.time = 0.0f;
	initialData.NoiseScale = 4.5562;
	initialData.NoiseAmplitudeFactor = 2.251255;
	initialData.NoiseFrequencyFactor = 5.2190124;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(VS_CONSTANT_BUFFER);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = &initialData;

	return device->CreateBuffer(&desc, &data, &m_buffer) == S_OK;
}

ID3D11Buffer* VolumetricExplosionConstantBuffer::GetPSBuffer()
{
	return m_buffer;
}
