#include "stdafx.h"
#include "StandardTransparentMaterialDrawCommand.h"

#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffer.h"
#include "Engine/Core/ResourceTypes/Material.h"

#include "Engine/Core/RTTI/TypedObjectManager.h"

StandardTransparentMaterialDrawCommand::~StandardTransparentMaterialDrawCommand()
{
    m_constantBuffer.ReleaseBuffer();
}

void StandardTransparentMaterialDrawCommand::PreDrawAll()
{
	m_rasterizerState.SetState({ kCullStateBackCull, kFillModeSolid, true });
    m_blendState.SetState({ kBlendSrc, kBlendDestInv, kBlendOpAdd });

    m_constantBuffer.BindBuffer(0, BIND_ALL);
}

bool StandardTransparentMaterialDrawCommand::BindMaterial(MeshRenderer& mrc)
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