#include "stdafx.h"
#include "StandardMaterialDrawCommand.h"

#include "Engine/Core/Graphics/ResourceTypes/Material/StandardMaterial.hpp"

StandardMaterialDrawCommand::StandardMaterialDrawCommand()
{

}

StandardMaterialDrawCommand::~StandardMaterialDrawCommand()
{
    m_constantBuffer.ReleaseBuffer();
}

void StandardMaterialDrawCommand::PreDrawAll()
{
    GraphicsSystem* gs = GetSystemManager().GetSystem<GraphicsSystem>();
    gs->GetRasterizerState()->SetCullState(kCullStateBackCull);

    m_constantBuffer.BindBuffer();
}

bool StandardMaterialDrawCommand::BindMaterial(MeshRendererComponent& mrc)
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
