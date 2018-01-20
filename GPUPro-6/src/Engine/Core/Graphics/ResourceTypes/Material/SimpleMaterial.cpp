#include "stdafx.h"
#include "SimpleMaterial.h"

#include "Engine/Core/ResourceManagement/ResourceManager.h"


bool Material<void>::BindIfValid()
{
    if (m_shaderIndex > -1)
    {
        Shader* s = GetResourceManager().GetAsset<Shader>(m_shaderIndex);
        if (s != nullptr && s->SetCurrentIfValid())
        {
            for (size_t i = 0; i < m_shaderResources.size(); ++i)
            {
                ResourceDetails rd = m_shaderResources[i];
                ShaderResource* tex = GetResourceManager().GetAsset<ShaderResource>(rd.m_resourceIndex);
                if (tex != nullptr)
                {
                    tex->BindResource(static_cast<UINT>(rd.m_slotIndex));
                }
            }

            for (size_t i = 0; i < m_textureSamplerIndexes.size(); ++i)
            {
                ResourceDetails rd = m_textureSamplerIndexes[i];
                TextureSampler* ts = GetResourceManager().GetAsset<TextureSampler>(rd.m_resourceIndex);
                if (ts != nullptr)
                {
                    ts->BindTextureSampler(static_cast<UINT>(rd.m_slotIndex));
                }
            }
            return true;
        }
    }
    return false;
}