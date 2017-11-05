#pragma once

#include "DataStructures/Color.h"
#include "Components/ComponentType.hpp"

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

struct InitLight
{
    Light operator()()
    {
        Light newLight;
        ZeroMemory(&newLight, sizeof(newLight));
        return newLight;
    }
};

typedef ComponentRegistrationInfo<Light, 3, InitLight> LightComponent;