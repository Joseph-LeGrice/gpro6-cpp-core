#pragma once

#include "Engine/Core/SceneGraph/Components/Util/ComponentType.hpp"

struct MeshRenderer
{
    int m_meshIndex;
    //int m_drawCommandIndex; // 'How to draw me'
    int m_materialIndex; // 'How I am special'
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