#pragma once
#include "D3DX11.h"
#include "D3DX10.h"
#include "GraphicsSystem.h"

template<class T>
class ConstantBuffer
{
	friend class ConstantBufferManagementSystem;

public:
	bool Initialize()
	{
		T initialData;
		ZeroMemory(&initialData, sizeof(T));

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(T);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = &initialData;

		ID3D11Device* device = GraphicsSystem::Instance()->GetGraphicsDevice();
		return SUCCEEDED(device->CreateBuffer(&desc, &data, &m_buffer));
	}

	void UpdateBuffer(T& data)
	{
		D3D11_MAPPED_SUBRESOURCE mappedData;

		ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
		HRESULT bufferMapResult = deviceContext->Map(m_buffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &mappedData);
		if (SUCCEEDED(bufferMapResult))
		{
			memcpy(mappedData.pData, &data, sizeof(T));
			deviceContext->Unmap(m_buffer, 0);
		}
	}

	ID3D11Buffer* const GetBuffer()
	{
		return m_buffer;
	}

private:
	ConstantBuffer()
	{
		m_buffer = nullptr;
	}

	~ConstantBuffer()
	{
		SAFE_RELEASE(m_buffer);
	}

	ID3D11Buffer* m_buffer;
};
