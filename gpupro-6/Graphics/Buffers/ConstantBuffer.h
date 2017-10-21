#pragma once
#pragma warning(push)
#pragma warning(disable: 4127)

#include "D3DX11.h"
#include "D3DX10.h"
#include "Systems\GraphicsSystem.h"
#include "Utilities\Logging.h"

enum BindFlags
{
	BIND_VERTEX = 1 << 0,
	BIND_HULL   = 1 << 1,
	BIND_DOMAIN = 1 << 2,
	BIND_GEOM   = 1 << 3,
	BIND_PIXEL  = 1 << 4,
	BIND_ALL    = BIND_VERTEX | BIND_HULL | BIND_DOMAIN | BIND_GEOM | BIND_PIXEL
};

template<class T, UINT m_bufferSlot, BindFlags m_bindFlags>
class ConstantBuffer
{
	friend class ConstantBufferManagementSystem;
	
	static_assert(sizeof(T) % 16 == 0, "Constant Buffer size must be divisible by 16");
	static_assert(sizeof(T) <= D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT, "Constant Buffer size must be less than or equal to D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT");

public:
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

	void BindBuffer()
	{
		ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
		if ((m_bindFlags & BIND_VERTEX) == BIND_VERTEX)
		{
			deviceContext->VSSetConstantBuffers(m_bufferSlot, 1, &m_buffer);
		}
		if ((m_bindFlags & BIND_HULL) == BIND_HULL)
		{
			deviceContext->HSSetConstantBuffers(m_bufferSlot, 1, &m_buffer);
		}
		if ((m_bindFlags & BIND_DOMAIN) == BIND_DOMAIN)
		{
			deviceContext->DSSetConstantBuffers(m_bufferSlot, 1, &m_buffer);
		}
		if ((m_bindFlags & BIND_GEOM) == BIND_GEOM)
		{
			deviceContext->GSSetConstantBuffers(m_bufferSlot, 1, &m_buffer);
		}
		if ((m_bindFlags & BIND_PIXEL) == BIND_PIXEL)
		{
			deviceContext->PSSetConstantBuffers(m_bufferSlot, 1, &m_buffer);
		}
	}

private:
	ConstantBuffer()
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
		if (!SUCCEEDED(device->CreateBuffer(&desc, &data, &m_buffer)))
		{
			LogError("[ConstantBuffer] Could not Create Buffer!");
		}
	}

	~ConstantBuffer()
	{
		SAFE_RELEASE(m_buffer);
	}

	ID3D11Buffer* m_buffer;
};

#pragma warning(pop)