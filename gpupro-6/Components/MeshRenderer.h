#pragma once

#include "Components/ComponentType.hpp"

struct MeshRenderer
{
    //TODO: MeshRenderer- thoughts. Maybe instead of simple int's, m_meshIndex, m_materialIndex should reference a defined "Resource". Create a new 'ResourceReference' struct which could encode a type and an id. may require serialization to exist, each resource type could be loaded in their own way.
    int m_meshIndex;
    int m_materialIndex;
};

namespace MeshRendererInternal
{
    struct InitMeshRenderer
    {
        MeshRenderer operator()()
        {
            MeshRenderer mr;
            mr.m_meshIndex = -1;
            mr.m_materialIndex = -1;
            return mr;
        }
    };
}

typedef ComponentRegistrationInfo<MeshRenderer, 4, MeshRendererInternal::InitMeshRenderer> MeshRendererComponent;