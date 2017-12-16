#pragma once

#include "Core/DataStructures/Color.h"
#include "Core/SceneGraph/Components/Util/ComponentType.hpp"

enum LightType
{
    kLightType_Point = 0,
    kLightType_Spotlight = 1,
    kLightType_Directional = 2
};

struct Light
{
    Color m_color;
    FLOAT m_range;
    FLOAT m_intensity;
    FLOAT m_spotlightAngle;
    LightType m_type;
};

namespace LightInternal
{
    struct InitLight
    {
        Light operator()()
        {
            Light newLight;
            ZeroMemory(&newLight, sizeof(newLight));
            newLight.m_type = kLightType_Point;
            newLight.m_range = 100.0f;
            newLight.m_color = Color::White();
            newLight.m_intensity = 1.0f;

            return newLight;
        }
    };
}

typedef ComponentRegistrationInfo<Light, 3, LightInternal::InitLight> LightComponent;