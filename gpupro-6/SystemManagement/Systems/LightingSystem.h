#pragma once
#include "SystemManagement/ISystem.h"
#include "DataStructures/Vector4.h"
#include "DataStructures/Vector2.h"
#include "DataStructures/Color.h"
#include "Components/Light.h"

struct LIGHT_BUFFER
{
    Vector4 PositionWS;
    Vector4 DirectionWS;
    Vector4 PositionVS;
    Vector4 DirectionVS;
    Color Color;
    FLOAT SpotlightAngle;
    FLOAT Range;
    FLOAT Intensity;
    BOOL Enabled;
    BOOL Selected;
    UINT16 Type;
    Vector2 Padding;
};


class LightingSystem : public ISystem
{
public:
    LightingSystem();
    virtual ~LightingSystem();

    virtual bool Initialize() override;
    virtual void VariableTick() override;

    int GetBufferResourceIndex();

private:
    int m_lightBufferIndex;
};