#pragma once
#include "Engine/Core/ResourceManagement/IResource.h"
#include "Engine/Core/ResourceManagement/ResourceTypeMapping.h"

struct ID3D11Resource;
struct D3D11_SHADER_RESOURCE_VIEW_DESC;
struct ID3D11ShaderResourceView;
class GraphicsDevice;

class ShaderResource : public IResource
{
public:
    void BindResource(UINT resourceIndex);
    bool CreateViewWithResource(ID3D11Resource& resource, D3D11_SHADER_RESOURCE_VIEW_DESC* desc);

    virtual void Release() override;
	static const RegisterResource<ShaderResource, 2> static_registration;

protected:
    ManualRelease<ID3D11ShaderResourceView> m_resourceView;
};

