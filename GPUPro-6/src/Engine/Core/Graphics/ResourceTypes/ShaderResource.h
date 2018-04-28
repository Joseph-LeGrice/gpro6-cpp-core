#pragma once
#include "Engine/Core/RTTI/ITypedObject.h"


struct ID3D11Resource;
struct D3D11_SHADER_RESOURCE_VIEW_DESC;
struct ID3D11ShaderResourceView;
class GraphicsDevice;

class ShaderResource : public ITypedObject
{
REGISTER_TYPE(ShaderResource);
public:
    void BindResource(UINT resourceIndex);
    bool CreateViewWithResource(ID3D11Resource& resource, D3D11_SHADER_RESOURCE_VIEW_DESC* desc);

    virtual void Finalize() override;

protected:
    ManualRelease<ID3D11ShaderResourceView> m_resourceView;
};
