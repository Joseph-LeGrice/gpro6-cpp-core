#pragma once
#include "SystemManagement/GameSystem.h"
#include "DataStructures/Vector4.h"
#include "DataStructures/Vector2.h"

struct LIGHT_BUFFER
{
    Vector4 PositionWS;
    Vector4 DirectionWS;
    Vector4 PositionVS;
    Vector4 DirectionVS;
    Vector4 Color;
    FLOAT SpotlightAngle;
    FLOAT Range;
    FLOAT Intensity;
    BOOL Enabled;
    BOOL Selected;
    UINT16 Type;
    Vector2 Padding;
};

enum LightType
{
    kLightType_Point = 0,
    kLightType_Spotlight = 1,
    kLightType_Directional = 2
};

class LightingSystem : public ISystem
{
    REGISTER_SUBSYSTEM(LightingSystem);

public:
    virtual bool Initialize() override;
    virtual void VariableTick() override;

    int GetBufferResourceIndex();

private:
    int m_lightBufferIndex;
};