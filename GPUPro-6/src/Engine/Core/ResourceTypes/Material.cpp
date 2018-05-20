#include "stdafx.h"
#include "Material.h"

#include "Engine/Core/Graphics/Buffers/ConstantBuffer.h"
#include "Engine/Core/ResourceTypes/Shader.h"
#include "Engine/Core/ResourceTypes/ShaderResource.h"
#include "Engine/Core/ResourceTypes/TextureSampler.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/GlobalStaticReferences.h"

bool Material::BindIfValid(ConstantBuffer* buffer)
{
	if (m_shaderIndex > -1)
	{
		Shader* s = GlobalStaticReferences::Instance()->GetTypedObjectManager()->GetInstance<Shader>(m_shaderIndex);
		if (s != nullptr && s->SetCurrentIfValid())
		{
			if (buffer != nullptr)
			{
				buffer->UpdateBuffer(m_properties.GetData(), m_properties.GetDataLength());
			}

			for (size_t i = 0; i < m_shaderResources.size(); ++i)
			{
				ResourceDetails rd = m_shaderResources[i];
				ShaderResource* tex = GlobalStaticReferences::Instance()->GetTypedObjectManager()->GetInstance<ShaderResource>(rd.m_resourceIndex);
				if (tex != nullptr)
				{
					tex->BindResource(static_cast<UINT>(rd.m_slotIndex));
				}
			}

			for (size_t i = 0; i < m_textureSamplerIndexes.size(); ++i)
			{
				ResourceDetails rd = m_textureSamplerIndexes[i];
				TextureSampler* ts = GlobalStaticReferences::Instance()->GetTypedObjectManager()->GetInstance<TextureSampler>(rd.m_resourceIndex);
				if (ts != nullptr)
				{
					ts->BindTextureSampler(static_cast<UINT>(rd.m_slotIndex));
				}
			}
			return true;
		}
	}
	return false;
}

void Material::SetInteger(std::wstring name, int value)
{
	m_properties.SetInteger(name, value);
}

void Material::SetFloat(std::wstring name, float value)
{
	m_properties.SetFloat(name, value);
}

void Material::SetFloat2(std::wstring name, Vector2 value)
{
	m_properties.SetFloat2(name, value);
}

void Material::SetFloat3(std::wstring name, Vector3 value)
{
	m_properties.SetFloat3(name, value);
}

void Material::SetFloat4(std::wstring name, Vector4 value)
{
	m_properties.SetFloat4(name, value);
}

void Material::SetMatrix3x3(std::wstring name, Matrix3x3 value)
{
	m_properties.SetMatrix3x3(name, value);
}

void Material::SetMatrix4x4(std::wstring name, Matrix4x4 value)
{
	m_properties.SetMatrix4x4(name, value);
}

void Material::SetShaderIndex(int shaderIndex)
{
	m_shaderIndex = shaderIndex;
}

void Material::RegisterShaderResource(int resourceIndex, int slotIndex)
{
	m_shaderResources.push_back({ resourceIndex, slotIndex });
}

void Material::AddTextureSampler(int resourceIndex, int slotIndex)
{
	m_textureSamplerIndexes.push_back({ resourceIndex, slotIndex });
}
