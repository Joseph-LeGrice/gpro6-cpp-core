#include "stdafx.h"
#include "TextureSampler.h"
#include "GraphicsSystem.h"


TextureSampler::TextureSampler()
{
	m_sampler = nullptr;
}


TextureSampler::~TextureSampler()
{
	SAFE_RELEASE(m_sampler);
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

	ID3D11Device* device = GraphicsSystem::Instance()->GetGraphicsDevice();
	HRESULT createSamplerResult = device->CreateSamplerState(&desc, &m_sampler);
	return createSamplerResult == S_OK;
}

ID3D11SamplerState* TextureSampler::GetSampler()
{
	return m_sampler;
}
