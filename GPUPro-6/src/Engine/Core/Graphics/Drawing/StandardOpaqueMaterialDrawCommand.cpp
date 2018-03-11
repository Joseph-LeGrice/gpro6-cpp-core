#include "stdafx.h"
#include "StandardOpaqueMaterialDrawCommand.h"

#include "Engine/Core/Graphics/ResourceTypes/Material/StandardMaterial.hpp"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"

StandardOpaqueMaterialDrawCommand::~StandardOpaqueMaterialDrawCommand()
{
    m_constantBuffer->ReleaseBuffer();
}

void StandardOpaqueMaterialDrawCommand::PreDrawAll()
{
	m_rasterizerState->SetState({ kCullStateBackCull, kFillModeSolid, true });
    m_blendState->SetState({ false });

    m_constantBuffer->BindBuffer();
}

bool StandardOpaqueMaterialDrawCommand::BindMaterial(MeshRendererComponent& mrc)
{
    StandardMaterial* mat = GetResourceManager().GetAsset<StandardMaterial>(mrc.m_data.m_materialIndex);
    if (mat->BindIfValid())
    {
        m_constantBuffer->UpdateBuffer(mat->GetData());
        return true;
    }
    else
    {
        return false;
    }
}
