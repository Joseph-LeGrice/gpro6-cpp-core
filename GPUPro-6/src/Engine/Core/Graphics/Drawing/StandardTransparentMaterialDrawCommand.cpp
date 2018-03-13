#include "stdafx.h"
#include "StandardTransparentMaterialDrawCommand.h"

#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/StandardMaterialBuffer.h"

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

bool StandardTransparentMaterialDrawCommand::BindMaterial(MeshRendererComponent& mrc)
{
    StandardMaterial* mat = GetResourceManager().GetAsset<StandardMaterial>(mrc.m_data.m_materialIndex);
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