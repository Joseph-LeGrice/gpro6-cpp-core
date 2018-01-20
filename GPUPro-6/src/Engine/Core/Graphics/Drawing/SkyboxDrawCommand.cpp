#include "stdafx.h"
#include "SkyboxDrawCommand.h"

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/SystemManagement/SystemManager.h"

void SkyboxDrawCommand::PreDrawAll()
{
    GraphicsSystem* gs = GetSystemManager().GetSystem<GraphicsSystem>();
    gs->GetRasterizerState()->SetCullState(kCullStateFrontCull);
}

bool SkyboxDrawCommand::BindMaterial(MeshRendererComponent& mrc)
{
    StandardMaterial* mat = GetResourceManager().GetAsset<StandardMaterial>(mrc.m_data.m_materialIndex);
    return mat->BindIfValid();
}
