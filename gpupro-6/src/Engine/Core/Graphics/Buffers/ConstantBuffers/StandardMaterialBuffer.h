#pragma once
#include "ConstantBuffer.h"

struct MATERIAL_BUFFER
{
    Vector4 GlobalAmbient;
    Vector4 AmbientColor;
    Vector4 EmissiveColor;
    Vector4 DiffuseColor;
    Vector4 SpecularColor;
    Vector4 Reflectance;

    FLOAT Opacity;
    FLOAT SpecularPower;
    FLOAT IndexOfRefraction;
    BOOL HasAmbientTexture;

    BOOL HasEmissiveTexture;
    BOOL HasDiffuseTexture;
    BOOL HasSpecularTexture;
    BOOL HasSpecularPowerTexture;

    BOOL HasNormalTexture;
    BOOL HasBumpTexture;
    BOOL HasOpacityTexture;
    FLOAT BumpIntensity;

    FLOAT SpecularScale;
    FLOAT AlphaThreshold;
    Vector2 Padding;
};

struct MATERIAL_BUFFER_CONTAINER
{
    MATERIAL_BUFFER buf;
};

class StandardMaterialBuffer : public ConstantBuffer
{
public:
    StandardMaterialBuffer(GraphicsDevice& gfxDevice);
    void PushData(const MATERIAL_BUFFER_CONTAINER& data);
protected:
    virtual UINT GetBufferSlot() override;
    virtual BindFlags GetBindFlags() override;
};

