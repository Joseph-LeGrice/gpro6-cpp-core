#include "stdafx.h"
#include "ConstantBuffer.h"
#include "GameSystem.h"
#include "GraphicsSystem.h"

struct VS_CONSTANT_BUFFER
{
	Matrix4x4 WorldMatrix;
	Matrix4x4 ViewProjectionMatrix;
	float time;
	float NoiseScale;
	float NoiseAmplitudeFactor;
	float NoiseFrequencyFactor;
};

ConstantBuffer::ConstantBuffer()
{
	Matrix4x4::MatrixIdentity(&m_wMatrix);
	Matrix4x4::MatrixIdentity(&m_vpMatrix);
	m_buffer = nullptr;
}


ConstantBuffer::~ConstantBuffer()
{
}

bool ConstantBuffer::Initialize(ID3D11Device* device)
{
	Matrix4x4 m;
	Matrix4x4::MatrixIdentity(&m);

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

void ConstantBuffer::SetViewProjectionMatrix(Matrix4x4 vp)
{
	m_vpMatrix = vp;
}

void ConstantBuffer::SetWorldMatrix(Matrix4x4 w)
{
	m_wMatrix = w;
}

void ConstantBuffer::SetBuffers()
{
	ID3D11DeviceContext* deviceContext = GameSystem::Graphics()->GetGraphicsDeviceContext();
	deviceContext->VSSetConstantBuffers(0, 1, &m_buffer);
	deviceContext->HSSetConstantBuffers(0, 1, &m_buffer);
	deviceContext->DSSetConstantBuffers(0, 1, &m_buffer);
	deviceContext->GSSetConstantBuffers(0, 1, &m_buffer);
	deviceContext->PSSetConstantBuffers(0, 1, &m_buffer);
}

void ConstantBuffer::UpdateBuffers()
{
	D3D11_MAPPED_SUBRESOURCE mappedData;

	ID3D11DeviceContext* deviceContext = GameSystem::Graphics()->GetGraphicsDeviceContext();
	HRESULT bufferMapResult = deviceContext->Map(m_buffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DYNAMIC, &mappedData);
	if (bufferMapResult == S_OK)
	{
		VS_CONSTANT_BUFFER data = GetBufferData();
		memcpy(mappedData.pData, &data, sizeof(VS_CONSTANT_BUFFER));
		deviceContext->Unmap(m_buffer, 0);
	}
}

VS_CONSTANT_BUFFER ConstantBuffer::GetBufferData()
{
	VS_CONSTANT_BUFFER data;
	data.WorldMatrix = m_wMatrix; 
	data.ViewProjectionMatrix = m_vpMatrix;
	data.time = 0.0f;
	data.NoiseScale = 4.5562;
	data.NoiseAmplitudeFactor = 2.251255;
	data.NoiseFrequencyFactor = 5.2190124;

	return data;
}

