#include "stdafx.h"
#include "SkyboxDrawCommand.h"

#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/Components/MeshRenderer.h"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"
#include "Engine/Core/ResourceTypes/Material.h"


void SkyboxDrawCommand::PreDrawAll()
{
	m_rasterizerState.SetState({ kCullStateFrontCull, kFillModeSolid, true });
	m_blendState.SetState({ false });
}

bool SkyboxDrawCommand::BindMaterial(MeshRenderer& mrc)
{
    Material* mat = m_typedObjectManager.GetInstance<Material>(mrc.m_materialIndex);
    return mat->BindIfValid(nullptr);
}
