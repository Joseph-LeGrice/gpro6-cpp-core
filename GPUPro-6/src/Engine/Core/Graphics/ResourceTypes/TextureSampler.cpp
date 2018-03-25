#include "stdafx.h"
#include "TextureSampler.h"

#include "D3D11.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/ResourceManagement/ResourceReferences.h"

void TextureSampler::BindTextureSampler(UINT samplerIndex)
{
	ID3D11DeviceContext* deviceContext = GetResourceReferences().GetGraphicsDevice().GetGraphicsDeviceContext();
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

	ID3D11Device* device = GetResourceReferences().GetGraphicsDevice().GetGraphicsDevice();
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
