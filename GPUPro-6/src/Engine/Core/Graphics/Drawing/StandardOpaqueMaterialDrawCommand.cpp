#include "stdafx.h"
#include "StandardOpaqueMaterialDrawCommand.h"

#include "Engine/Core/Graphics/Buffers/ConstantBuffers/StandardMaterialBuffer.h"
#include "Engine/Core/Graphics/ResourceTypes/Material/StandardMaterial.hpp"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"

StandardOpaqueMaterialDrawCommand::~StandardOpaqueMaterialDrawCommand()
{
    m_constantBuffer.ReleaseBuffer();
}

void StandardOpaqueMaterialDrawCommand::PreDrawAll()
{
	m_rasterizerState.SetState({ kCullStateBackCull, kFillModeSolid, true });
    m_blendState.SetState({ false });

    m_constantBuffer.BindBuffer();
}

bool StandardOpaqueMaterialDrawCommand::BindMaterial(MeshRenderer& mrc)
{
    StandardMaterial* mat = m_resourceManager.GetResource<StandardMaterial>(mrc.m_materialIndex);
    if (mat->BindIfValid())
    {
        m_constantBuffer.PushData(mat->GetData());
        return true;
    }
    else
    {
        return false;
    }
}
