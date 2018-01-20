#include "stdafx.h"
#include "Engine/Core/Graphics/ResourceTypes/TextureSampler.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/SystemManagement/SystemManager.h"

TextureSampler::TextureSampler(UINT ai) : IResource(ai) { }
TextureSampler::TextureSampler() : IResource() { }
TextureSampler::~TextureSampler() { }

void TextureSampler::BindTextureSampler(UINT samplerIndex)
{
	ID3D11DeviceContext* deviceContext = GetSystemManager().GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
    deviceContext->VSSetSamplers(samplerIndex, 1, m_sampler);
    deviceContext->HSSetSamplers(samplerIndex, 1, m_sampler);
    deviceContext->DSSetSamplers(samplerIndex, 1, m_sampler);
    deviceContext->GSSetSamplers(samplerIndex, 1, m_sampler);
    deviceContext->PSSetSamplers(samplerIndex, 1, m_sampler);
}

bool TextureSampler::Initialize()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
	desc.Filter = D3D11_FILTER_ANISOTROPIC;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	//desc.MipLODBias;
	desc.MaxAnisotropy = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_GREATER;
	//desc.BorderColor[4];
	desc.MinLOD = 0;
	desc.MaxLOD = 0;

	ID3D11Device* device = GetSystemManager().GetSystem<GraphicsSystem>()->GetGraphicsDevice();
	HRESULT createSamplerResult = device->CreateSamplerState(&desc, m_sampler);
	return SUCCEEDED(createSamplerResult);
}

bool TextureSampler::IsValid()
{
	return m_sampler != nullptr;
}

void TextureSampler::Release()
{
    m_sampler.ReleasePointer();
}
