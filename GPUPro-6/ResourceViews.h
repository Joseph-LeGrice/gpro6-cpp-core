#pragma once

#include "D3D11.h"
#include <vector>

class ResourceViews
{
public:
	ResourceViews();
	~ResourceViews();

	virtual bool Initialize(ID3D11Device* device) = 0;
	virtual std::vector<ID3D11ShaderResourceView*>* GetVSResources();
	virtual std::vector<ID3D11ShaderResourceView*>* GetHSResources();
	virtual std::vector<ID3D11ShaderResourceView*>* GetDSResources();
	virtual std::vector<ID3D11ShaderResourceView*>* GetGSResources();
	virtual std::vector<ID3D11ShaderResourceView*>* GetPSResources();


	////TODO: Separate this stuff out
	//D3D11_SAMPLER_DESC desc;
	//ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
	//desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	//desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	//desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	//desc.MipLODBias = 0.0f;
	//desc.MaxAnisotropy = 1;
	//desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	//desc.BorderColor[0] = 0;
	//desc.BorderColor[1] = 0;
	//desc.BorderColor[2] = 0;
	//desc.BorderColor[3] = 0;
	//desc.MinLOD = 0;
	//desc.MaxLOD = D3D11_FLOAT32_MAX;
	//bool createSamplerState = device->CreateSamplerState(&desc, &m_sampleState) == S_OK;

};

