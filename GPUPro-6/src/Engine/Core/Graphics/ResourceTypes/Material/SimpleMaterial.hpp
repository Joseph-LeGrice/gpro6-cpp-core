//#pragma once
//
//#include "Engine/Core/ResourceManagement/ResourceManager.h"
//#include "Material.hpp"
//
//template<>
//class Material<void> : public IResource
//{
//public:
//    struct ResourceDetails
//    {
//        int m_resourceIndex;
//        int m_slotIndex;
//    };
//
//    Material(int resourceId) : IResource(resourceId) { }
//    Material() : IResource() { }
//    ~Material() { }
//
//    bool BindIfValid()
//    {
//        if (m_shaderIndex > -1)
//        {
//            Shader* s = GetResourceManager().GetAsset<Shader>(m_shaderIndex);
//            if (s != nullptr && s->SetCurrentIfValid())
//            {
//                for (size_t i = 0; i < m_shaderResources.size(); ++i)
//                {
//                    ResourceDetails rd = m_shaderResources[i];
//                    ShaderResource* tex = GetResourceManager().GetAsset<ShaderResource>(rd.m_resourceIndex);
//                    if (tex != nullptr)
//                    {
//                        tex->BindResource(static_cast<UINT>(rd.m_slotIndex));
//                    }
//                }
//
//                for (size_t i = 0; i < m_textureSamplerIndexes.size(); ++i)
//                {
//                    ResourceDetails rd = m_textureSamplerIndexes[i];
//                    TextureSampler* ts = GetResourceManager().GetAsset<TextureSampler>(rd.m_resourceIndex);
//                    if (ts != nullptr)
//                    {
//                        ts->BindTextureSampler(static_cast<UINT>(rd.m_slotIndex));
//                    }
//                }
//                return true;
//            }
//        }
//        return false;
//    }
//
//    void SetShaderIndex(UINT16 shaderIndex)
//    {
//        m_shaderIndex = shaderIndex;
//    }
//
//    void RegisterShaderResource(ResourceDetails rd)
//    {
//        m_shaderResources.push_back(rd);
//    }
//
//    void AddTextureSampler(ResourceDetails rd)
//    {
//        m_textureSamplerIndexes.push_back(rd);
//    }
//
//    void Release() override
//    {
//    }
//
//private:
//    int m_shaderIndex = -1;
//    std::vector<ResourceDetails> m_shaderResources;
//    std::vector<ResourceDetails> m_textureSamplerIndexes;
//};
//
//typedef Material<void> SimpleMaterial;
