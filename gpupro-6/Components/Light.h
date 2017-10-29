#pragma once

#include "DataStructures/Color.h"

enum LightType
{
    kLightType_Point = 0,
    kLightType_Spotlight = 1,
    kLightType_Directional = 2
};

struct Light
{
    int m_entityIndex;
    Color m_color;
    FLOAT m_range;
    FLOAT m_intensity;
    FLOAT m_spotlightAngle;
    LightType m_type;
};

struct LightTransformMap
{
    int m_transformIndex;
    int m_lightIndex;
};
