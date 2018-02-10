#include "stdafx.h"
#include "StandardTransparentMaterialDrawCommand.h"
#include "Engine/Core/SystemManagement/SystemManager.h"


StandardTransparentMaterialDrawCommand::StandardTransparentMaterialDrawCommand()
{
}


StandardTransparentMaterialDrawCommand::~StandardTransparentMaterialDrawCommand()
{
    m_constantBuffer.ReleaseBuffer();
}

void StandardTransparentMaterialDrawCommand::PreDrawAll()
{
    GraphicsSystem* gs = GetSystemManager().GetSystem<GraphicsSystem>();
    gs->GetRasterizerState()->SetState({ kCullStateBackCull, kFillModeSolid, true });
    gs->GetBlendState()->SetState({ kBlendSrc, kBlendDestInv, kBlendOpAdd });

    m_constantBuffer.BindBuffer();
}

bool StandardTransparentMaterialDrawCommand::BindMaterial(MeshRendererComponent& mrc)
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