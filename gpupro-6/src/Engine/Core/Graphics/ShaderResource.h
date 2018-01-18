#pragma once
#include "Engine/Core/ResourceManagement/IResource.h"
#include "D3D11.h"

class ShaderResource : public IResource
{
public:
    ShaderResource() : IResource() { }
    ShaderResource(UINT resourceId) : IResource(resourceId) { }
    ~ShaderResource() { }

    void BindResource(UINT resourceIndex);
    bool CreateViewWithResource(ID3D11Resource& resource, D3D11_SHADER_RESOURCE_VIEW_DESC* desc);

    virtual void Release() override;

protected:
    ManualRelease<ID3D11ShaderResourceView> m_resourceView;
};

