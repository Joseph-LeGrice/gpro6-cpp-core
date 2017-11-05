#pragma once

#include "Components/ComponentType.hpp"

struct MeshRenderer
{
    int m_meshIndex;
    int m_materialIndex;
};

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

typedef ComponentRegistrationInfo<MeshRenderer, 4, InitMeshRenderer> MeshRendererComponent;