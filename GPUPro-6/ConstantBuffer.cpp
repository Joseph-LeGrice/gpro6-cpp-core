#include "stdafx.h"
#include "ConstantBuffer.h"

struct VS_CONSTANT_BUFFER
{
	Matrix4x4 MVP;
	float time;
	float NoiseScale;
	float NoiseAmplitudeFactor;
	float NoiseFrequencyFactor;
};

ConstantBuffer::ConstantBuffer()
{
	m_buffer = nullptr;
}


ConstantBuffer::~ConstantBuffer()
{
}

bool ConstantBuffer::Initialize(ID3D11Device* device)
{
	Matrix4x4 m;
	Matrix4x4::MatrixIdentity(&m);

	VS_CONSTANT_BUFFER initialData = GetBufferData(m);

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

ID3D11Buffer* ConstantBuffer::GetVSBuffer()
{
	return m_buffer;
}

ID3D11Buffer* ConstantBuffer::GetHSBuffer()
{
	return m_buffer;
}

ID3D11Buffer* ConstantBuffer::GetDSBuffer()
{
	return m_buffer;
}

ID3D11Buffer* ConstantBuffer::GetGSBuffer()
{
	return m_buffer;
}

ID3D11Buffer* ConstantBuffer::GetPSBuffer()
{
	return m_buffer;
}

void ConstantBuffer::SetModelViewProjectionMatrix(Matrix4x4 mvp, ID3D11DeviceContext* context)
{
	VS_CONSTANT_BUFFER data = GetBufferData(mvp);

	D3D11_MAPPED_SUBRESOURCE mappedData;
	context->Map(m_buffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &mappedData);
	memcpy(mappedData.pData, &data, sizeof(VS_CONSTANT_BUFFER));
	context->Unmap(m_buffer, 0);
}

VS_CONSTANT_BUFFER ConstantBuffer::GetBufferData(Matrix4x4 transform)
{
	VS_CONSTANT_BUFFER data;
	data.MVP = transform;
	data.time = 0.0f;
	data.NoiseScale = 4.5562;
	data.NoiseAmplitudeFactor = 2.251255;
	data.NoiseFrequencyFactor = 5.2190124;

	return data;
}
