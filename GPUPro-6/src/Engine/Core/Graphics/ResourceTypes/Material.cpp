#include "stdafx.h"

#include <vector>
#include <algorithm>

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Core/Graphics/Components/Transform.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "Engine/Core/SceneGraph/SceneGraph.h"
#include "Engine/Core/Graphics/ResourceTypes/Material.h"
#include "Engine/Core/Graphics/ResourceTypes/Shader.h"
#include "Engine/Core/Graphics/Buffers/VertexBuffer.h"
#include "Engine/Core/Graphics/Buffers/IndexBuffer.h"
#include "Engine/Core/Graphics/ResourceTypes/TextureSampler.h"
#include "Engine/Core/Graphics/GraphicsSystem.h"
#include "Engine/Core/Utilities/Logging.h"

Material::Material(UINT resourceId) : IResource(resourceId)
{
	m_shaderIndex = -1;
}

Material::~Material()
{
}

void Material::SetShaderIndex(UINT16 shaderIndex)
{
    m_shaderIndex = static_cast<int>(shaderIndex);
}

void Material::RegisterShaderResource(ShaderResourceDetails rd)
{
    m_shaderResources.push_back(rd);
}

void Material::AddTextureSampler(SamplerDetails rd)
{
	m_textureSamplerIndexes.push_back(rd);
}

void Material::Release()
{
}

bool Material::BindIfValid()
{
    if (m_shaderIndex > -1)
    {
        Shader* s = GetResourceManager().GetAsset<Shader>(m_shaderIndex);
        if (s != nullptr && s->SetCurrentIfValid())
        {
            for (size_t i = 0; i < m_shaderResources.size(); ++i)
            {
                ShaderResourceDetails rd = m_shaderResources[i];
                ShaderResource* tex = GetResourceManager().GetAsset<ShaderResource>(rd.m_resourceIndex);
                if (tex != nullptr)
                {
                    tex->BindResource(static_cast<UINT>(rd.m_slotIndex));
                }
            }

            for (size_t i = 0; i < m_textureSamplerIndexes.size(); ++i)
            {
                SamplerDetails rd = m_textureSamplerIndexes[i];
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
