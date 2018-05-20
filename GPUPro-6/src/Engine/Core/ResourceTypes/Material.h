#pragma once

#include <vector>

#include "Engine/Core/RTTI/ITypedObject.h"
#include "Engine/Core/DataStructures/MaterialPropertyList.h"

//struct MATERIAL_BUFFER
//{
//	Vector4 GlobalAmbient;
//	Vector4 AmbientColor;
//	Vector4 EmissiveColor;
//	Vector4 DiffuseColor;
//	Vector4 SpecularColor;
//	Vector4 Reflectance;
//
//	FLOAT Opacity;
//	FLOAT SpecularPower;
//	FLOAT IndexOfRefraction;
//	BOOL HasAmbientTexture;
//
//	BOOL HasEmissiveTexture;
//	BOOL HasDiffuseTexture;
//	BOOL HasSpecularTexture;
//	BOOL HasSpecularPowerTexture;
//
//	BOOL HasNormalTexture;
//	BOOL HasBumpTexture;
//	BOOL HasOpacityTexture;
//	FLOAT BumpIntensity;
//
//	FLOAT SpecularScale;
//	FLOAT AlphaThreshold;
//	Vector2 Padding;
//};
//
//struct MATERIAL_BUFFER_CONTAINER
//{
//	MATERIAL_BUFFER buf;
//};

class ConstantBuffer;

class Material : public ITypedObject
{
REGISTER_TYPE(Material);
public:
	bool BindIfValid(ConstantBuffer* buffer);

	void SetInteger(std::wstring name, int value);
	void SetBoolean(std::wstring name, bool value);
	void SetFloat(std::wstring name, float value);
	void SetFloat2(std::wstring name, Vector2 value);
	void SetFloat3(std::wstring name, Vector3 value);
	void SetFloat4(std::wstring name, Vector4 value);
	void SetMatrix3x3(std::wstring name, Matrix3x3 value);
	void SetMatrix4x4(std::wstring name, Matrix4x4 value);

    void SetShaderIndex(int shaderIndex);
	void RegisterShaderResource(int resourceIndex, int slotIndex);
	void AddTextureSampler(int resourceIndex, int slotIndex);

private:
	struct ResourceDetails
	{
		int m_resourceIndex;
		int m_slotIndex;
	};

    int m_shaderIndex = -1;
	MaterialPropertyList m_properties;
	std::vector<ResourceDetails> m_shaderResources;
	std::vector<ResourceDetails> m_textureSamplerIndexes;
};
