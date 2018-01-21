#pragma once
#include "IDrawCommand.h"
#include "Engine/Core/Graphics/Buffers/ConstantBufferInterface.h"

class StandardTransparentMaterialDrawCommand : public IDrawCommand<3>
{
public:
    StandardTransparentMaterialDrawCommand();
    ~StandardTransparentMaterialDrawCommand();

protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRendererComponent& mrc) override;

private:
    ConstantBuffer<MATERIAL_BUFFER_CONTAINER, MATERIAL_BUFFER_SLOT, BIND_ALL> m_constantBuffer;
};

