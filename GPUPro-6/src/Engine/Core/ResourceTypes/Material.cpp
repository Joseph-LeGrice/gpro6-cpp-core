#include "stdafx.h"
#include "Material.h"

#include "Engine/Core/Graphics/GraphicsSystem.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffer.h"
#include "Engine/Core/ResourceTypes/Shader.h"
#include "Engine/Core/ResourceTypes/ShaderResource.h"
#include "Engine/Core/ResourceTypes/TextureSampler.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/GlobalStaticReferences.h"

bool Material::BindIfValid(RasterizerState* rasterizerState, BlendState* blendState)
{
	if (m_shader)
	{
		Shader* s = m_shader.Get<Shader>();
		if (s != nullptr && s->SetCurrentIfValid())
		{
			blendState->SetState(m_blendState);
			rasterizerState->SetState(m_rasterState);

			if (m_buffer != nullptr)
			{
				m_buffer->UpdateBuffer(m_properties.GetData(), m_properties.GetDataLength());
			}

			for (size_t i = 0; i < m_shaderResources.size(); ++i)
			{
				ResourceDetails rd = m_shaderResources[i];
				ShaderResource* tex = rd.m_resourceIndex.Get<ShaderResource>();
				if (tex != nullptr)
				{
					tex->BindResource(static_cast<UINT>(rd.m_slotIndex));
				}
			}

			for (size_t i = 0; i < m_textureSamplerIndexes.size(); ++i)
			{
				ResourceDetails rd = m_textureSamplerIndexes[i];
				TextureSampler* ts = rd.m_resourceIndex.Get<TextureSampler>();
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

void Material::InitProperties(std::vector<MaterialProperty::Initializer> props)
{
	m_properties.Initalize(props);

	GraphicsSystem* gs = GlobalStaticReferences::Instance()->GetGraphicsSystem();
	m_buffer = gs->CreateConstantBuffer(m_properties.GetDataLength());
}

void Material::SetInteger(std::wstring name, int value)
{
	m_properties.SetInteger(name, value);
}

void Material::SetBoolean(std::wstring name, bool value)
{
	m_properties.SetBoolean(name, value);
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

void Material::SetCullState(CullState cullState)
{
	m_rasterState.m_cullState = cullState;
}

void Material::SetFillMode(FillMode fillMode)
{
	m_rasterState.m_fillMode = fillMode;
}

void Material::SetBlendingEnabled(bool enabled)
{
	m_blendState.m_blendEnabled = enabled;
}

void Material::SetColorBlending(BlendFactor src, BlendFactor dest, BlendOperation op)
{
	m_blendState.m_srcColor = src;
	m_blendState.m_destColor = dest;
	m_blendState.m_colorBlendOp= op;
}

void Material::SetAlphaBlending(BlendFactor src, BlendFactor dest, BlendOperation op)
{
	m_blendState.m_srcAlpha = src;
	m_blendState.m_destAlpha = dest;
	m_blendState.m_alphaBlendOp = op;
}

void Material::SetShader(ToPtr shader)
{
	m_shader = shader;
}

void Material::RegisterShaderResource(ToPtr resourceIndex, int slotIndex)
{
	m_shaderResources.push_back({ resourceIndex, slotIndex });
}

void Material::AddTextureSampler(ToPtr resourceIndex, int slotIndex)
{
	m_textureSamplerIndexes.push_back({ resourceIndex, slotIndex });
}
