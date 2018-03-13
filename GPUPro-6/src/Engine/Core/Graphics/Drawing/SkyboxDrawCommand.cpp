#include "stdafx.h"
#include "SkyboxDrawCommand.h"

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"


void SkyboxDrawCommand::PreDrawAll()
{
	m_rasterizerState.SetState({ kCullStateFrontCull, kFillModeSolid, true });
	m_blendState.SetState({ false });
}

bool SkyboxDrawCommand::BindMaterial(MeshRendererComponent& mrc)
{
    SimpleMaterial* mat = GetResourceManager().GetAsset<SimpleMaterial>(mrc.m_data.m_materialIndex);
    return mat->BindIfValid();
}
