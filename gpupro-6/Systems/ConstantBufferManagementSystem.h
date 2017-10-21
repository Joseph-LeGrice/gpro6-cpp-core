#pragma once

#include "Graphics/Buffers/ConstantBuffer.h"
#include "Systems/GameSystem.h"

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

//#define NUM_BUFFERS 2
typedef ConstantBuffer<PER_OBJECT_BUFFER, 0, BIND_ALL> PerObjectBuffer;
typedef ConstantBuffer<MATERIAL_BUFFER_CONTAINER, 1, BIND_ALL> MaterialBuffer;

class ConstantBufferManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(ConstantBufferManagementSystem);

	REGISTER_BUFFER(PerObjectBuffer);
	REGISTER_BUFFER(MaterialBuffer);
};
