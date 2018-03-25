#pragma once

#include <vector>
#include "Engine/Core/ResourceManagement/IResource.h"
#include "Engine/Core/ResourceManagement/ResourceReferences.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Graphics/ResourceTypes/Shader.h"
#include "Engine/Core/Graphics/ResourceTypes/ShaderResource.h"
#include "Engine/Core/Graphics/ResourceTypes/TextureSampler.h"

template<class T> // TODO: COULD ALSO PASS IN NUM OF TEXTURES ALLOWED HERE?
class Material : public IResource
{
public:
    struct ResourceDetails
    {
        int m_resourceIndex;
        int m_slotIndex;
    };

    Material(size_t resourceIndex, ResourceReferences& resourceReferences) : IResource(resourceIndex, resourceReferences) { }

    bool BindIfValid()
    {
        if (m_shaderIndex > -1)
        {
            Shader* s = GetResourceReferences().GetResourceManager().GetAsset<Shader>(m_shaderIndex);
            if (s != nullptr && s->SetCurrentIfValid())
            {
                for (size_t i = 0; i < m_shaderResources.size(); ++i)
                {
                    ResourceDetails rd = m_shaderResources[i];
                    ShaderResource* tex = GetResourceReferences().GetResourceManager().GetAsset<ShaderResource>(rd.m_resourceIndex);
                    if (tex != nullptr)
                    {
                        tex->BindResource(static_cast<UINT>(rd.m_slotIndex));
                    }
                }

                for (size_t i = 0; i < m_textureSamplerIndexes.size(); ++i)
                {
                    ResourceDetails rd = m_textureSamplerIndexes[i];
                    TextureSampler* ts = GetResourceReferences().GetResourceManager().GetAsset<TextureSampler>(rd.m_resourceIndex);
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

    T& GetData()
    {
        return m_data;
    }

    void SetData(T data)
    {
        m_data = data;
    }

    void SetShaderIndex(UINT16 shaderIndex)
    {
        m_shaderIndex = shaderIndex;
    }

    void RegisterShaderResource(ResourceDetails rd)
    {
        m_shaderResources.push_back(rd);
    }

    void AddTextureSampler(ResourceDetails rd)
    {
        m_textureSamplerIndexes.push_back(rd);
    }

private:
    T m_data = T();
    int m_shaderIndex = -1;
    std::vector<ResourceDetails> m_shaderResources;
	std::vector<ResourceDetails> m_textureSamplerIndexes;
};

template<>
class Material<void> : public IResource
{
public:
	struct ResourceDetails
	{
		int m_resourceIndex;
		int m_slotIndex;
	};

	Material(size_t resourceIndex, ResourceReferences& resourceReferences) : IResource(resourceIndex, resourceReferences) { }

	bool BindIfValid()
	{
		if (m_shaderIndex > -1)
		{
			Shader* s = GetResourceReferences().GetResourceManager().GetAsset<Shader>(m_shaderIndex);
			if (s != nullptr && s->SetCurrentIfValid())
			{
				for (size_t i = 0; i < m_shaderResources.size(); ++i)
				{
					ResourceDetails rd = m_shaderResources[i];
					ShaderResource* tex = GetResourceReferences().GetResourceManager().GetAsset<ShaderResource>(rd.m_resourceIndex);
					if (tex != nullptr)
					{
						tex->BindResource(static_cast<UINT>(rd.m_slotIndex));
					}
				}

				for (size_t i = 0; i < m_textureSamplerIndexes.size(); ++i)
				{
					ResourceDetails rd = m_textureSamplerIndexes[i];
					TextureSampler* ts = GetResourceReferences().GetResourceManager().GetAsset<TextureSampler>(rd.m_resourceIndex);
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

	void SetShaderIndex(UINT16 shaderIndex)
	{
		m_shaderIndex = shaderIndex;
	}

	void RegisterShaderResource(ResourceDetails rd)
	{
		m_shaderResources.push_back(rd);
	}

	void AddTextureSampler(ResourceDetails rd)
	{
		m_textureSamplerIndexes.push_back(rd);
	}

	void Release() override
	{
	}

private:
	int m_shaderIndex = -1;
	std::vector<ResourceDetails> m_shaderResources;
	std::vector<ResourceDetails> m_textureSamplerIndexes;
};
