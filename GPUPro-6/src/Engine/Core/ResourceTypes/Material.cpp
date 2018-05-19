#include "stdafx.h"
#include "Material.h"

#include "Engine/Core/ResourceTypes/Shader.h"
#include "Engine/Core/ResourceTypes/ShaderResource.h"
#include "Engine/Core/ResourceTypes/TextureSampler.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/GlobalStaticReferences.h"

bool Material::BindIfValid()
{
	if (m_shaderIndex > -1)
	{
		Shader* s = GlobalStaticReferences::Instance()->GetTypedObjectManager()->GetInstance<Shader>(m_shaderIndex);
		if (s != nullptr && s->SetCurrentIfValid())
		{
			for (size_t i = 0; i < m_shaderResources.size(); ++i)
			{
				ResourceDetails rd = m_shaderResources[i];
				ShaderResource* tex = GlobalStaticReferences::Instance()->GetTypedObjectManager()->GetInstance<ShaderResource>(rd.m_resourceIndex);
				if (tex != nullptr)
				{
					tex->BindResource(static_cast<UINT>(rd.m_slotIndex));
				}
			}

			for (size_t i = 0; i < m_textureSamplerIndexes.size(); ++i)
			{
				ResourceDetails rd = m_textureSamplerIndexes[i];
				TextureSampler* ts = GlobalStaticReferences::Instance()->GetTypedObjectManager()->GetInstance<TextureSampler>(rd.m_resourceIndex);
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

size_t Material::GetDataLength()
{
	return 0;
}

void* Material::GetData()
{
	return nullptr;
}

void Material::SetShaderIndex(int shaderIndex)
{
	m_shaderIndex = shaderIndex;
}

void Material::RegisterShaderResource(int resourceIndex, int slotIndex)
{
	m_shaderResources.push_back({ resourceIndex, slotIndex });
}

void Material::AddTextureSampler(int resourceIndex, int slotIndex)
{
	m_textureSamplerIndexes.push_back({ resourceIndex, slotIndex });
}
