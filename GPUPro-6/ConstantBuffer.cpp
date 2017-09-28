#include "stdafx.h"
#include "ConstantBuffer.h"
#include "GraphicsSystem.h"

ConstantBuffer::ConstantBuffer()
{
	Matrix4x4::Identity(m_wMatrix);
	Matrix4x4::Identity(m_vMatrix);
	Matrix4x4::Identity(m_pMatrix);
	m_buffer = nullptr;
}


ConstantBuffer::~ConstantBuffer()
{
	SAFE_RELEASE(m_buffer);
}

bool ConstantBuffer::Initialize(ID3D11Device* device)
{
	Matrix4x4 m;
	Matrix4x4::Identity(m);

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

	return SUCCEEDED(device->CreateBuffer(&desc, &data, &m_buffer));
}

void ConstantBuffer::SetViewMatrix(const Matrix4x4& v)
{
	m_vMatrix = v;
}

void ConstantBuffer::SetProjectionMatrix(const Matrix4x4& p)
{
	m_pMatrix = p;
}

void ConstantBuffer::SetWorldMatrix(const Matrix4x4& w)
{
	m_wMatrix = w;
}

void ConstantBuffer::SetBuffers()
{
	ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
	deviceContext->VSSetConstantBuffers(0, 1, &m_buffer);
	deviceContext->HSSetConstantBuffers(0, 1, &m_buffer);
	deviceContext->DSSetConstantBuffers(0, 1, &m_buffer);
	deviceContext->GSSetConstantBuffers(0, 1, &m_buffer);
	deviceContext->PSSetConstantBuffers(0, 1, &m_buffer);
}

void ConstantBuffer::UpdateBuffers()
{
	D3D11_MAPPED_SUBRESOURCE mappedData;

	ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
	HRESULT bufferMapResult = deviceContext->Map(m_buffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &mappedData);
	if (SUCCEEDED(bufferMapResult))
	{
		VS_CONSTANT_BUFFER data = GetBufferData();
		memcpy(mappedData.pData, &data, sizeof(VS_CONSTANT_BUFFER));
		deviceContext->Unmap(m_buffer, 0);
	}
}

VS_CONSTANT_BUFFER ConstantBuffer::GetBufferData()
{
	VS_CONSTANT_BUFFER data;
	data.MVP = m_pMatrix * m_vMatrix * m_wMatrix;
	data.WorldMatrix = m_wMatrix; 
	data.ViewProjectionMatrix = m_vMatrix * m_pMatrix;

	return data;
}

