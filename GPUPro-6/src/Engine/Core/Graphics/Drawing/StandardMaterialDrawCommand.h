#pragma once

#include "IDrawCommand.h"
#include "Engine/Core/Graphics/Buffers/ConstantBufferInterface.h"
#include "Engine/Core/Graphics/ResourceTypes/StandardMaterial.hpp"

class StandardMaterialDrawCommand : public IDrawCommand
{
public:
    StandardMaterialDrawCommand();
    ~StandardMaterialDrawCommand();

    virtual void Draw(Matrix4x4 view, Matrix4x4 proj) override;

private:
    ConstantBuffer<MATERIAL_BUFFER_CONTAINER, MATERIAL_BUFFER_SLOT, BIND_ALL> m_constantBuffer;
};
