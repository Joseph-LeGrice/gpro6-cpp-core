#include "stdafx.h"
#include "SkyboxDrawCommand.h"

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/SystemManagement/SystemManager.h"

void SkyboxDrawCommand::PreDrawAll()
{
    GraphicsSystem* gs = GetSystemManager().GetSystem<GraphicsSystem>();
    gs->GetRasterizerState()->SetState({ kCullStateFrontCull, true });
}

bool SkyboxDrawCommand::BindMaterial(MeshRendererComponent& mrc)
{
    SimpleMaterial* mat = GetResourceManager().GetAsset<SimpleMaterial>(mrc.m_data.m_materialIndex);
    return mat->BindIfValid();
}
