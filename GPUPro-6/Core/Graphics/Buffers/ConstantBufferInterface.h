#pragma once

#include <tuple>
#include "Core/Graphics/Buffers/ConstantBuffer.h"

#include "Core/DataStructures/Vector2.h"
#include "Core/DataStructures/Vector4.h"

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

template<typename... Types>
class ConstantBufferInterfaceImpl
{
public:
    template<class T>
    T& GetBuffer()
    {
        return std::get<T>(m_constantBuffers);
    }

    ConstantBufferInterfaceImpl() = default;
    ~ConstantBufferInterfaceImpl() = default;
    ConstantBufferInterfaceImpl(ConstantBufferInterfaceImpl&) = delete;

private:
    std::tuple<Types...> m_constantBuffers;
};

typedef ConstantBuffer<PER_CAMERA_BUFFER, 0, BIND_ALL> PerCameraBuffer;
typedef ConstantBuffer<PER_OBJECT_BUFFER, 1, BIND_ALL> PerObjectBuffer;
typedef ConstantBuffer<MATERIAL_BUFFER_CONTAINER, 2, BIND_ALL> MaterialBuffer;

typedef ConstantBufferInterfaceImpl<
    PerCameraBuffer,
    PerObjectBuffer,
    MaterialBuffer
> ConstantBufferInterface;

extern ConstantBufferInterface* s_buffer;

void InitConstantBufferInterface();
ConstantBufferInterface& GetConstantBufferInterface();
void DestroyConstantBufferInterface();