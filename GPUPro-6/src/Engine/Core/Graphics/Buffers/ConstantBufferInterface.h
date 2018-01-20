#pragma once

#include <tuple>
#include "Engine/Core/Graphics/Buffers/ConstantBuffer.h"

#include "MyMath/Matrix/Matrix4x4.h"
#include "MyMath/Vector/Vector2.h"
#include "MyMath/Vector/Vector4.h"

struct PER_CAMERA_BUFFER
{
    Vector4 EyePos;
    Matrix4x4 View;
    Matrix4x4 Projection;
};

struct PER_OBJECT_BUFFER
{
	Matrix4x4 ModelViewProjection;
	Matrix4x4 ModelView;
};

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

const int MATERIAL_BUFFER_SLOT = 2;

typedef ConstantBuffer<PER_CAMERA_BUFFER, 0, BIND_ALL> PerCameraBuffer;
typedef ConstantBuffer<PER_OBJECT_BUFFER, 1, BIND_ALL> PerObjectBuffer;
typedef ConstantBuffer<MATERIAL_BUFFER_CONTAINER, MATERIAL_BUFFER_SLOT, BIND_ALL> StandardMaterialBuffer;

typedef ConstantBufferInterfaceImpl<
    PerCameraBuffer,
    PerObjectBuffer,
    StandardMaterialBuffer
> ConstantBufferInterface;

extern ConstantBufferInterface* s_buffer;

void InitConstantBufferInterface();
ConstantBufferInterface& GetConstantBufferInterface();
void DestroyConstantBufferInterface();