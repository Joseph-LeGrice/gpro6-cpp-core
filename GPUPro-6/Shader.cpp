#include "stdafx.h"
#include "Shader.h"

#include "D3DX11.h"

#include "VertexData.h"
#include "GraphicsSystem.h"
#include "TextureSampler.h"
#include "ShaderResource.h"
#include <algorithm>
#include <vector>

Shader::Shader()
{
	m_inputLayout = nullptr;
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
	m_geometryShader = nullptr;
	m_hullShader = nullptr;
	m_domainShader = nullptr;
	m_shaderResources = new std::vector<ShaderResource*>();
	m_textureSamplers = new std::vector<TextureSampler*>();
}


Shader::~Shader()
{
	SAFE_RELEASE(m_inputLayout);
	SAFE_RELEASE(m_vertexShader);
	SAFE_RELEASE(m_hullShader);
	SAFE_RELEASE(m_domainShader);
	SAFE_RELEASE(m_geometryShader);
	SAFE_RELEASE(m_pixelShader);
	
	SAFE_DELETE_VECTOR_HEAP(m_textureSamplers);
	SAFE_DELETE_VECTOR_HEAP(m_shaderResources);
}


bool Shader::Initialize(std::wstring filename)
{
	ID3D11Device* device = GraphicsSystem::Instance()->GetGraphicsDevice();
	bool vertexShaderCompiled = InitVertexShader(filename, "VShader", device);
	bool hullShaderCompiled = true; // = m_shader->InitHullShader(filename, "HShader", device);
	bool domainShaderCompiled = true; //= m_shader->InitDomainShader(filename, "DShader", device);
	bool geometryShaderCompiled = true; // = m_shader->InitGeometryShader(filename, "GShaderTessellation", device);
	bool pixelShaderCompiled = InitPixelShader(filename, "PShader", device);

	return (vertexShaderCompiled && hullShaderCompiled && domainShaderCompiled && geometryShaderCompiled && pixelShaderCompiled);
}

bool Shader::SetCurrentIfValid()
{
	if (m_vertexShader == nullptr || m_inputLayout == nullptr || m_pixelShader == nullptr)
	{
		return false;
	}
	else
	{
		ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
		deviceContext->IASetInputLayout(m_inputLayout);
		deviceContext->VSSetShader(m_vertexShader, NULL, 0);

		if (m_hullShader != nullptr && m_domainShader != nullptr)
		{
			deviceContext->HSSetShader(m_hullShader, NULL, 0);
			deviceContext->DSSetShader(m_domainShader, NULL, 0);
		}

		if (m_geometryShader != nullptr)
		{
			deviceContext->GSSetShader(m_geometryShader, 0, 0);
		}

		deviceContext->PSSetShader(m_pixelShader, NULL, 0);

		if (m_shaderResources->size() > 0)
		{
			std::vector<ID3D11ShaderResourceView*> allResources;
			for each (ShaderResource* sr in *m_shaderResources)
			{
				ID3D11ShaderResourceView* resource = sr->GetResourceView();
				allResources.push_back(resource);
			}
			deviceContext->VSSetShaderResources(0, (UINT)allResources.size(), &allResources[0]);
			//deviceContext->HSSetShaderResources(0, allResources.size(), &allResources[0]);
			//deviceContext->DSSetShaderResources(0, allResources.size(), &allResources[0]);
			//deviceContext->GSSetShaderResources(0, allResources.size(), &allResources[0]);
			deviceContext->PSSetShaderResources(0, (UINT)allResources.size(), &allResources[0]);
		}

		if (m_textureSamplers->size() > 0)
		{
			std::vector<ID3D11SamplerState*> allSamplers;
			for each (TextureSampler* ts in *m_textureSamplers)
			{
				ID3D11SamplerState* sampler = ts->GetSampler();
				allSamplers.push_back(sampler);
			}
			deviceContext->VSSetSamplers(0, (UINT)allSamplers.size(), &allSamplers[0]);
			//deviceContext->HSSetSamplers(0, allSamplers.size(), &allSamplers[0]);
			//deviceContext->DSSetSamplers(0, allSamplers.size(), &allSamplers[0]);
			//deviceContext->GSSetSamplers(0, allSamplers.size(), &allSamplers[0]);
			deviceContext->PSSetSamplers(0, (UINT)allSamplers.size(), &allSamplers[0]);
		}

		return true;
	}
}


void Shader::AddShaderResource(ShaderResource* r)
{
	m_shaderResources->push_back(r);
}

void Shader::RemoveShaderResource(ShaderResource* r)
{
	m_shaderResources->erase(std::remove(m_shaderResources->begin(), m_shaderResources->end(), r), m_shaderResources->end());
}


void Shader::AddTextureSampler(TextureSampler* ts)
{
	m_textureSamplers->push_back(ts);
}

void Shader::RemoveTextureSampler(TextureSampler* ts)
{
	m_textureSamplers->erase(std::remove(m_textureSamplers->begin(), m_textureSamplers->end(), ts), m_textureSamplers->end());
}

bool Shader::InitVertexShader(std::wstring filename, std::string name, ID3D11Device* device)
{
	ID3D10Blob* vertexShaderBlob = nullptr;
	ID3D10Blob* vertexShaderErrorBlob = nullptr;
	HRESULT vertexShaderCompileResult = D3DX11CompileFromFile(filename.c_str(), 0, 0, name.c_str(), "vs_5_0", 0, 0, 0, &vertexShaderBlob, &vertexShaderErrorBlob, 0);
	if (vertexShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)vertexShaderErrorBlob->GetBufferPointer());
		SAFE_RELEASE(vertexShaderErrorBlob);
	}

	if (SUCCEEDED(vertexShaderCompileResult))
	{
		HRESULT createdVertexShader  = device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &m_vertexShader);
		if (SUCCEEDED(createdVertexShader))
		{
			HRESULT attachedInputLayout = device->CreateInputLayout(g_inputLayoutScheme, 3, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &m_inputLayout);

			SAFE_RELEASE(vertexShaderBlob);

			return SUCCEEDED(attachedInputLayout);
		}
	}

	return false;
}


bool Shader::InitHullShader(std::wstring filename, std::string name, ID3D11Device* device)
{
	ID3D10Blob* hullShaderBlob = nullptr;
	ID3D10Blob* hullShaderErrorBlob = nullptr;
	HRESULT hullShaderCompileResult = D3DX11CompileFromFile(filename.c_str(), 0, 0, name.c_str(), "hs_5_0", 0, 0, 0, &hullShaderBlob, &hullShaderErrorBlob, 0);
	if (hullShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)hullShaderErrorBlob->GetBufferPointer());
		SAFE_RELEASE(hullShaderErrorBlob);
	}

	if (SUCCEEDED(hullShaderCompileResult))
	{
		HRESULT createdHullShader = device->CreateHullShader(hullShaderBlob->GetBufferPointer(), hullShaderBlob->GetBufferSize(), NULL, &m_hullShader);
		SAFE_RELEASE(hullShaderBlob);

		return SUCCEEDED(createdHullShader);
	}
	else
	{
		return false;
	}
}


bool Shader::InitDomainShader(std::wstring filename, std::string name, ID3D11Device* device)
{
	ID3D10Blob* domainShaderBlob = nullptr;
	ID3D10Blob* domainShaderErrorBlob = nullptr;
	HRESULT domainShaderCompileResult = D3DX11CompileFromFile(filename.c_str(), 0, 0, name.c_str(), "ds_5_0", 0, 0, 0, &domainShaderBlob, &domainShaderErrorBlob, 0);
	if (domainShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)domainShaderErrorBlob->GetBufferPointer());
		SAFE_RELEASE(domainShaderErrorBlob);
	}

	if (SUCCEEDED(domainShaderCompileResult))
	{
		HRESULT createdDomainShader = device->CreateDomainShader(domainShaderBlob->GetBufferPointer(), domainShaderBlob->GetBufferSize(), 0, &m_domainShader);
		SAFE_RELEASE(domainShaderBlob);

		return SUCCEEDED(createdDomainShader);
	}
	else
	{
		return false;
	}
}


bool Shader::InitGeometryShader(std::wstring filename, std::string name, ID3D11Device* device)
{
	ID3D10Blob* geomShaderBlob = nullptr;
	ID3D10Blob* geomShaderErrorBlob = nullptr;
	HRESULT geomShaderCompileResult = D3DX11CompileFromFile(filename.c_str(), 0, 0, name.c_str(), "gs_5_0", 0, 0, 0, &geomShaderBlob, &geomShaderErrorBlob, 0);
	if (geomShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)geomShaderErrorBlob->GetBufferPointer());
		SAFE_RELEASE(geomShaderErrorBlob);
	}

	if (SUCCEEDED(geomShaderCompileResult))
	{
		HRESULT createdGeometryShader = device->CreateGeometryShader(geomShaderBlob->GetBufferPointer(), geomShaderBlob->GetBufferSize(), NULL, &m_geometryShader);
		SAFE_RELEASE(geomShaderBlob);

		return SUCCEEDED(createdGeometryShader);
	}
	else
	{
		return false;
	}
}

	
bool Shader::InitPixelShader(std::wstring filename, std::string name, ID3D11Device* device)
{
	ID3D10Blob* pixelShaderBlob = nullptr;
	ID3D10Blob* pixelShaderErrorBlob = nullptr;
	HRESULT pixelShaderCompileResult = D3DX11CompileFromFile(filename.c_str(), 0, 0, name.c_str(), "ps_5_0", 0, 0, 0, &pixelShaderBlob, &pixelShaderErrorBlob, 0);
	if (pixelShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)pixelShaderErrorBlob->GetBufferPointer());
		SAFE_RELEASE(pixelShaderErrorBlob);
	}

	if (SUCCEEDED(pixelShaderCompileResult))
	{
		HRESULT createdPixelShader = device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, &m_pixelShader);
		SAFE_RELEASE(pixelShaderBlob);

		return SUCCEEDED(createdPixelShader);
	}
	else
	{
		return false;
	}
}
