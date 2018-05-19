#include "stdafx.h"
#include "StandardOpaqueMaterialDrawCommand.h"

#include "Engine/Core/Graphics/Buffers/ConstantBuffer.h"

#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"
#include "Engine/Core/ResourceTypes/Material.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

StandardOpaqueMaterialDrawCommand::~StandardOpaqueMaterialDrawCommand()
{
    m_constantBuffer.ReleaseBuffer();
}

void StandardOpaqueMaterialDrawCommand::PreDrawAll()
{
	m_rasterizerState.SetState({ kCullStateBackCull, kFillModeSolid, true });
    m_blendState.SetState({ false });

    m_constantBuffer.BindBuffer(3, BIND_ALL);
}

bool StandardOpaqueMaterialDrawCommand::BindMaterial(MeshRenderer& mrc)
{
    Material* mat = m_typedObjectManager.GetInstance<Material>(mrc.m_materialIndex);
    if (mat->BindIfValid())
    {
        m_constantBuffer.UpdateBuffer(mat->GetData(), mat->GetDataLength());
        return true;
    }
    else
    {
        return false;
    }
}
