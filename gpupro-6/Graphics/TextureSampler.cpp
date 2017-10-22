#include "stdafx.h"
#include "Graphics/TextureSampler.h"
#include "SystemManagement/Systems/GraphicsSystem.h"
#include "SystemManagement/Systems/MaterialManagementSystem.h"

TextureSampler::TextureSampler()
{
	m_sampler = nullptr;
}


TextureSampler::~TextureSampler()
{
	SAFE_RELEASE(m_sampler);
}

void TextureSampler::BindTextureSampler(UINT samplerIndex)
{
	ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
	deviceContext->VSSetSamplers(samplerIndex, 1, &m_sampler);
	deviceContext->HSSetSamplers(samplerIndex, 1, &m_sampler);
	deviceContext->DSSetSamplers(samplerIndex, 1, &m_sampler);
	deviceContext->GSSetSamplers(samplerIndex, 1, &m_sampler);
	deviceContext->PSSetSamplers(samplerIndex, 1, &m_sampler);
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
	return SUCCEEDED(createSamplerResult);
}

bool TextureSampler::IsValid()
{
	return m_sampler != nullptr;
}

int CreateTextureSampler()
{
	TextureSampler* ts = new TextureSampler();
	if (ts->Initialize())
	{
		return MaterialManagementSystem::Instance()->RegisterTextureSampler(*ts);
	}
	else
	{
		SAFE_DELETE(ts);
		return -1;
	}
}
