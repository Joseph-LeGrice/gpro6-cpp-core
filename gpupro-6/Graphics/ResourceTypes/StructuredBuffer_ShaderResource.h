#pragma once
#include "ShaderResource.h"
#include "SystemManagement/SystemManager.h"

template<class T, UINT m_numberOfElements>
class StructuredBuffer_ShaderResource : ShaderResource
{
public:
	static int CreateNew()
	{
		ID3D11Buffer* buffer;

		D3D11_BUFFER_DESC bDesc;
		ZeroMemory(&bDesc, sizeof(D3D11_BUFFER_DESC));
		bDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bDesc.Usage = D3D11_USAGE_DYNAMIC;
		bDesc.ByteWidth = m_numberOfElements * sizeof(T);
		bDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bDesc.StructureByteStride = sizeof(T);

		ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();
		HRESULT createBufferResult = device->CreateBuffer(&bDesc, NULL, &buffer);
		if (!SUCCEEDED(createBufferResult))
		{
			return -1;
		}

		ID3D11ShaderResourceView* resourceView;

		D3D11_SHADER_RESOURCE_VIEW_DESC rvDesc;
		ZeroMemory(&rvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		rvDesc.Format = DXGI_FORMAT_UNKNOWN;
		rvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		rvDesc.Buffer.ElementWidth = m_numberOfElements;
		HRESULT createResourceViewResult = device->CreateShaderResourceView(buffer, &rvDesc, &resourceView);
		if (!SUCCEEDED(createResourceViewResult))
		{
			SAFE_RELEASE(buffer);
			return -1;
		}
	
		StructuredBuffer_ShaderResource* newInstance = new StructuredBuffer_ShaderResource();
		newInstance->m_buffer = buffer;
		newInstance->m_resourceView = resourceView;
		return AssetManager::Instance()->RegisterShaderResource((ShaderResource&)*newInstance);
	}

	void UpdateBuffer(T& newData)
	{
		D3D11_MAPPED_SUBRESOURCE mappedData;
		ID3D11DeviceContext* deviceContext = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
		HRESULT mapResult = deviceContext->Map(m_buffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &mappedData);
		if (SUCCEEDED(mapResult))
		{
			memcpy(mappedData.pData, &newData, sizeof(T));
			deviceContext->Unmap(m_buffer, 0);
		}
	}

protected:
	virtual ID3D11ShaderResourceView* GetResourceView() override
	{
		return m_resourceView;
	}

private:
	ID3D11Buffer* m_buffer;
	ID3D11ShaderResourceView* m_resourceView;

	StructuredBuffer_ShaderResource()
	{
		m_buffer = nullptr;
		m_resourceView = nullptr;
	}

	~StructuredBuffer_ShaderResource()
	{
		SAFE_RELEASE(m_buffer);
		SAFE_RELEASE(m_resourceView);
	}

	StructuredBuffer_ShaderResource(const StructuredBuffer_ShaderResource&) = delete;
};
