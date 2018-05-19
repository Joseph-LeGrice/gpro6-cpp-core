#pragma once

#include <vector>
#include "Engine/Core/RTTI/ITypedObject.h"

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

class Material : public ITypedObject
{
REGISTER_TYPE(Material);
public:
    struct ResourceDetails
    {
        int m_resourceIndex;
        int m_slotIndex;
    };

    void* GetData();
	size_t GetDataLength();

    bool BindIfValid();

	//void SetFloat4(std::string, Vector3);
	//void SetFloat3(std::string, Vector3);
	//void SetFloat2(std::string, Vector3);
	//void SetFloat(std::string, Vector3);
	//void SetInteger(std::string, Vector3);
	//void SetTexture(std::string, Vector3);
	//void SetTextureSampler(std::string, Vector3);

    void SetShaderIndex(int shaderIndex);
	void RegisterShaderResource(int resourceIndex, int slotIndex);
	void AddTextureSampler(int resourceIndex, int slotIndex);

private:
    int m_shaderIndex = -1;
    std::vector<ResourceDetails> m_shaderResources;
	std::vector<ResourceDetails> m_textureSamplerIndexes;
};
