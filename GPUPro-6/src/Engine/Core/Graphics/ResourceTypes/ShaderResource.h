#pragma once
#include "Engine/Core/ResourceManagement/IResource.h"


struct ID3D11Resource;
struct D3D11_SHADER_RESOURCE_VIEW_DESC;
struct ID3D11ShaderResourceView;
class GraphicsDevice;

class ShaderResource : public IResource
{
public:
    void BindResource(UINT resourceIndex);
    bool CreateViewWithResource(ID3D11Resource& resource, D3D11_SHADER_RESOURCE_VIEW_DESC* desc);

	virtual const char* GetTypeName() override
	{
		return TO_STRING(ShaderResource);
	}

    virtual void Release() override;

protected:
    ManualRelease<ID3D11ShaderResourceView> m_resourceView;
};
REGISTER_TYPE(ShaderResource, 2)
