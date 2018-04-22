#pragma once

#include "D3D11.h"
#include "Engine/Core/ResourceManagement/IResource.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/Graphics/ResourceTypes/ShaderResource.h"
#include "Engine/Core/GlobalStaticReferences.h"

class StructuredBuffer : public IResource
{
public:
    template<class T, UINT m_numberOfElements>
	bool CreateBuffer()
	{
		D3D11_BUFFER_DESC bDesc;
		ZeroMemory(&bDesc, sizeof(D3D11_BUFFER_DESC));
		bDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bDesc.Usage = D3D11_USAGE_DYNAMIC;
		bDesc.ByteWidth = m_numberOfElements * sizeof(T);
		bDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bDesc.StructureByteStride = sizeof(T);

		ID3D11Device* device = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDevice();
		HRESULT createBufferResult = device->CreateBuffer(&bDesc, NULL, m_buffer);
		if (!SUCCEEDED(createBufferResult))
		{
			return false;
		}


		D3D11_SHADER_RESOURCE_VIEW_DESC rvDesc;
		ZeroMemory(&rvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		rvDesc.Format = DXGI_FORMAT_UNKNOWN;
		rvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        rvDesc.Buffer.ElementWidth = m_numberOfElements;
        
        ShaderResource* myShaderResourceView = GlobalStaticReferences::Instance()->GetResourceManager()->CreateResource<ShaderResource>();
		m_myShaderResourceViewId = static_cast<int>(myShaderResourceView->GetInstanceID());
        
        bool createdView = myShaderResourceView->CreateViewWithResource(m_buffer, &rvDesc);
		if (!createdView)
        {
            m_buffer.ReleasePointer();
			GlobalStaticReferences::Instance()->GetResourceManager()->DestroyResource<ShaderResource>(m_myShaderResourceViewId);

            return false;
        }
        return true;
	}

    template<class T>
    void UpdateBuffer(T& newData)
	{
		D3D11_MAPPED_SUBRESOURCE mappedData;
		ID3D11DeviceContext* deviceContext = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDeviceContext();
		HRESULT mapResult = deviceContext->Map(m_buffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &mappedData);
		if (SUCCEEDED(mapResult))
		{
			memcpy(mappedData.pData, &newData, sizeof(T));
			deviceContext->Unmap(m_buffer, 0);
		}
	}

	void BindResource(UINT resourceIndex);
	
	virtual const char* GetTypeName() override
	{
		return TO_STRING(StructuredBuffer);
	}

    virtual void Release() override;

    int GetMyResourceViewID()
    {
        return m_myShaderResourceViewId;
    }

private:
    int m_myShaderResourceViewId = -1;
	ManualRelease<ID3D11Buffer> m_buffer;
};
REGISTER_RESOURCE(StructuredBuffer, 4)
