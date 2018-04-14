#pragma once
#include "Engine/Core/ResourceManagement/IResource.h"

struct ID3D11Resource;
struct D3D11_SHADER_RESOURCE_VIEW_DESC;
struct ID3D11ShaderResourceView;
class GraphicsDevice;

class ShaderResource : public IResource
{
public:
    ShaderResource(size_t resourceIndex) :
		IResource(resourceIndex) { }

    void BindResource(UINT resourceIndex);
    bool CreateViewWithResource(ID3D11Resource& resource, D3D11_SHADER_RESOURCE_VIEW_DESC* desc);

    virtual void Release() override;

	static ResourceTypeID GetResourceType()
	{
		return 2;
	}

protected:
    ManualRelease<ID3D11ShaderResourceView> m_resourceView;
};

