#pragma once

#include "ConstantBuffer.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector4.h"

#define NUM_BUFFERS 2

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

typedef ConstantBuffer<PER_OBJECT_BUFFER, 0, NUM_BUFFERS, BIND_ALL> PerObjectBuffer;
typedef ConstantBuffer<MATERIAL_BUFFER, 1, NUM_BUFFERS, BIND_ALL> MaterialBuffer;
