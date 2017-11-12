#pragma once

#include "Graphics/Buffers/ConstantBuffer.h"

#include "DataStructures/Vector2.h"
#include "DataStructures/Vector4.h"

#define REGISTER_BUFFER(bufferType) \
public: \
	bufferType& Get##bufferType##() \
	{ \
		return m_##bufferType##Buffer; \
	} \
private: \
	bufferType m_##bufferType##Buffer; \

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

typedef ConstantBuffer<PER_OBJECT_BUFFER, 0, BIND_ALL> PerObjectBuffer;
typedef ConstantBuffer<MATERIAL_BUFFER_CONTAINER, 1, BIND_ALL> MaterialBuffer;

class ConstantBufferInterface
{
    //TODO: Replace REGISTER_BUFFER macro with a std::tuple
	REGISTER_BUFFER(PerObjectBuffer);
	REGISTER_BUFFER(MaterialBuffer);

public:
    ConstantBufferInterface() = default;
    ~ConstantBufferInterface() = default;
    ConstantBufferInterface(ConstantBufferInterface&) = delete;
};
