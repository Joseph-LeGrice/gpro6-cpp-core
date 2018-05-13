#include "stdafx.h"
#include "StandardTransparentMaterialDrawCommand.h"

#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/StandardMaterialBuffer.h"
#include "Engine/Core/ResourceTypes/Material/StandardMaterial.hpp"
#include "Engine/Core/RTTI/TypedObjectManager.h"

StandardTransparentMaterialDrawCommand::~StandardTransparentMaterialDrawCommand()
{
    m_constantBuffer.ReleaseBuffer();
}

void StandardTransparentMaterialDrawCommand::PreDrawAll()
{
	m_rasterizerState.SetState({ kCullStateBackCull, kFillModeSolid, true });
    m_blendState.SetState({ kBlendSrc, kBlendDestInv, kBlendOpAdd });

    m_constantBuffer.BindBuffer();
}

bool StandardTransparentMaterialDrawCommand::BindMaterial(MeshRenderer& mrc)
{
    StandardMaterial* mat = m_typedObjectManager.GetInstance<StandardMaterial>(mrc.m_materialIndex);
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