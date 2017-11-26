#pragma once

#include "D3D11.h"
#include "AssetManagement/IResource.h"
#include "SystemManagement/SystemManager.h"

class StructuredBuffer : public IResource
{
public:
    StructuredBuffer(UINT resourceId);
    ~StructuredBuffer();

    void BindResource(UINT resourceIndex);

    template<class T, UINT m_numberOfElements>
	bool Initialize()
	{
		D3D11_BUFFER_DESC bDesc;
		ZeroMemory(&bDesc, sizeof(D3D11_BUFFER_DESC));
		bDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bDesc.Usage = D3D11_USAGE_DYNAMIC;
		bDesc.ByteWidth = m_numberOfElements * sizeof(T);
		bDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bDesc.StructureByteStride = sizeof(T);

		ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();
		HRESULT createBufferResult = device->CreateBuffer(&bDesc, NULL, &m_buffer);
		if (!SUCCEEDED(createBufferResult))
		{
			return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC rvDesc;
		ZeroMemory(&rvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		rvDesc.Format = DXGI_FORMAT_UNKNOWN;
		rvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		rvDesc.Buffer.ElementWidth = m_numberOfElements;
		HRESULT createResourceViewResult = device->CreateShaderResourceView(m_buffer, &rvDesc, &m_resourceView);
        if (!SUCCEEDED(createResourceViewResult))
        {
            SAFE_RELEASE(m_buffer);
            return false;
        }

        return true;
	}

    template<class T>
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

private:
	ID3D11Buffer* m_buffer;
	ID3D11ShaderResourceView* m_resourceView;
};
