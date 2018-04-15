#pragma once
#include "Engine/Core/ResourceManagement/IResource.h"
#include "Engine/Core/ResourceManagement/ResourceTypeMapping.h"

struct ID3D11Resource;
struct D3D11_SHADER_RESOURCE_VIEW_DESC;
struct ID3D11ShaderResourceView;
class GraphicsDevice;

class ShaderResource : public IResource
{
DEFINE_RESOURCE(ShaderResource)
public:
    void BindResource(UINT resourceIndex);
    bool CreateViewWithResource(ID3D11Resource& resource, D3D11_SHADER_RESOURCE_VIEW_DESC* desc);

    virtual void Release() override;

protected:
    ManualRelease<ID3D11ShaderResourceView> m_resourceView;
};
REGISTER_RESOURCE(ShaderResource, 2)
