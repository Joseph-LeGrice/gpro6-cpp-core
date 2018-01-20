#pragma once

#include "IDrawCommand.h"
#include "Engine/Core/Graphics/Buffers/ConstantBufferInterface.h"
#include "Engine/Core/Graphics/ResourceTypes/Material/StandardMaterial.hpp"

struct MeshRenderer;

class StandardMaterialDrawCommand : public IDrawCommand<0>
{
public:
    StandardMaterialDrawCommand();
    ~StandardMaterialDrawCommand();

protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRendererComponent& mrc) override;

private:
    ConstantBuffer<MATERIAL_BUFFER_CONTAINER, MATERIAL_BUFFER_SLOT, BIND_ALL> m_constantBuffer;
};
