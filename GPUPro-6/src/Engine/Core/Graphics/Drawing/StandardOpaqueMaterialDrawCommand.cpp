#include "stdafx.h"
#include "StandardOpaqueMaterialDrawCommand.h"

#include "Engine/Core/Graphics/ResourceTypes/Material/StandardMaterial.hpp"

StandardOpaqueMaterialDrawCommand::StandardOpaqueMaterialDrawCommand()
{

}

StandardOpaqueMaterialDrawCommand::~StandardOpaqueMaterialDrawCommand()
{
    m_constantBuffer.ReleaseBuffer();
}

void StandardOpaqueMaterialDrawCommand::PreDrawAll()
{
    GraphicsSystem* gs = GetSystemManager().GetSystem<GraphicsSystem>();
    gs->GetRasterizerState()->SetState({ kCullStateBackCull, kFillModeWireframe, true });
    gs->GetBlendState()->SetState({ false });

    m_constantBuffer.BindBuffer();
}

bool StandardOpaqueMaterialDrawCommand::BindMaterial(MeshRendererComponent& mrc)
{
    StandardMaterial* mat = GetResourceManager().GetAsset<StandardMaterial>(mrc.m_data.m_materialIndex);
    if (mat->BindIfValid())
    {
        m_constantBuffer.UpdateBuffer(mat->GetData());
        return true;
    }
    else
    {
        return false;
    }
}
