#include "stdafx.h"
#include "SkyboxDrawCommand.h"

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"
#include "Engine/Core/Graphics/ResourceTypes/Material/SimpleMaterial.h"


void SkyboxDrawCommand::PreDrawAll()
{
	m_rasterizerState.SetState({ kCullStateFrontCull, kFillModeSolid, true });
	m_blendState.SetState({ false });
}

bool SkyboxDrawCommand::BindMaterial(MeshRenderer& mrc)
{
    SimpleMaterial* mat = m_resourceManager.GetResource<SimpleMaterial>(mrc.m_materialIndex);
    return mat->BindIfValid();
}
