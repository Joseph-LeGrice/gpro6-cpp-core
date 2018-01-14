#pragma once
#include "Engine/Core/SystemManagement/ISystem.h"
#include "MyMath/Vector/Vector4.h"
#include "MyMath/Vector/Vector2.h"
#include "Engine/Core/DataStructures/Color.h"
#include "Engine/Core/Graphics/Components/Light.h"

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