#include "stdafx.h"
#include "glm/glm.hpp"
#include "VolumetricExplosionConstantBuffer.h"

struct VS_CONSTANT_BUFFER
{
	D3DMATRIX MVP;
	float time;
	float NoiseScale;
	float NoiseAmplitudeFactor;
	float NoiseFrequencyFactor;
};

VolumetricExplosionConstantBuffer::VolumetricExplosionConstantBuffer()
{
	m_buffer = nullptr;
	D3DXMatrixIdentity(&m_mvp);
}


VolumetricExplosionConstantBuffer::~VolumetricExplosionConstantBuffer()
{
}

bool VolumetricExplosionConstantBuffer::Initialize(ID3D11Device* device)
{
	VS_CONSTANT_BUFFER initialData = GetBufferData();
	
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

ID3D11Buffer* VolumetricExplosionConstantBuffer::GetVSBuffer()
{
	return m_buffer;
}

ID3D11Buffer* VolumetricExplosionConstantBuffer::GetHSBuffer()
{
	return m_buffer;
}

ID3D11Buffer* VolumetricExplosionConstantBuffer::GetDSBuffer()
{
	return m_buffer;
}

ID3D11Buffer* VolumetricExplosionConstantBuffer::GetGSBuffer()
{
	return m_buffer;
}

ID3D11Buffer* VolumetricExplosionConstantBuffer::GetPSBuffer()
{
	return m_buffer;
}

void VolumetricExplosionConstantBuffer::SetModelViewProjectionMatrix(D3DXMATRIX mvp, ID3D11DeviceContext* context)
{
	m_mvp = mvp;

	VS_CONSTANT_BUFFER data = GetBufferData();
	context->UpdateSubresource(m_buffer, 0, 0, &data, 0, 0);
}

VS_CONSTANT_BUFFER VolumetricExplosionConstantBuffer::GetBufferData()
{
	VS_CONSTANT_BUFFER data;
	data.MVP = m_mvp;
	data.time = 0.0f;
	data.NoiseScale = 4.5562;
	data.NoiseAmplitudeFactor = 2.251255;
	data.NoiseFrequencyFactor = 5.2190124;

	return data;
}
