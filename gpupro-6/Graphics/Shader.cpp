#include "stdafx.h"
#include "Graphics\Shader.h"

#include "D3DX11.h"

#include "DataStructures\VertexData.h"
#include "Systems\GraphicsSystem.h"
#include "Systems\ShaderManagementSystem.h"

Shader::Shader()
{
	m_inputLayout = nullptr;
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
	m_geometryShader = nullptr;
	m_hullShader = nullptr;
	m_domainShader = nullptr;
}


Shader::~Shader()
{
	SAFE_RELEASE(m_inputLayout);
	SAFE_RELEASE(m_vertexShader);
	SAFE_RELEASE(m_hullShader);
	SAFE_RELEASE(m_domainShader);
	SAFE_RELEASE(m_geometryShader);
	SAFE_RELEASE(m_pixelShader);
}


Shader* Shader::CreateNew()
{
	Shader* newShaderInstance = new Shader();
	ShaderManagementSystem::Instance()->RegisterShader(newShaderInstance);
	return newShaderInstance;
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

		return true;
	}
}

bool Shader::InitVertexShader(std::wstring filename, std::string name)
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
		ID3D11Device* device = GraphicsSystem::Instance()->GetGraphicsDevice();
		HRESULT createdVertexShader  = device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &m_vertexShader);
		if (SUCCEEDED(createdVertexShader))
		{
			HRESULT attachedInputLayout = device->CreateInputLayout(g_inputLayoutScheme, 5, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &m_inputLayout);

			SAFE_RELEASE(vertexShaderBlob);

			return SUCCEEDED(attachedInputLayout);
		}
	}

	return false;
}


bool Shader::InitHullShader(std::wstring filename, std::string name)
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
		ID3D11Device* device = GraphicsSystem::Instance()->GetGraphicsDevice();
		HRESULT createdHullShader = device->CreateHullShader(hullShaderBlob->GetBufferPointer(), hullShaderBlob->GetBufferSize(), NULL, &m_hullShader);
		SAFE_RELEASE(hullShaderBlob);

		return SUCCEEDED(createdHullShader);
	}
	else
	{
		return false;
	}
}


bool Shader::InitDomainShader(std::wstring filename, std::string name)
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
		ID3D11Device* device = GraphicsSystem::Instance()->GetGraphicsDevice();
		HRESULT createdDomainShader = device->CreateDomainShader(domainShaderBlob->GetBufferPointer(), domainShaderBlob->GetBufferSize(), 0, &m_domainShader);
		SAFE_RELEASE(domainShaderBlob);

		return SUCCEEDED(createdDomainShader);
	}
	else
	{
		return false;
	}
}


bool Shader::InitGeometryShader(std::wstring filename, std::string name)
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
		ID3D11Device* device = GraphicsSystem::Instance()->GetGraphicsDevice();
		HRESULT createdGeometryShader = device->CreateGeometryShader(geomShaderBlob->GetBufferPointer(), geomShaderBlob->GetBufferSize(), NULL, &m_geometryShader);
		SAFE_RELEASE(geomShaderBlob);

		return SUCCEEDED(createdGeometryShader);
	}
	else
	{
		return false;
	}
}

	
bool Shader::InitPixelShader(std::wstring filename, std::string name)
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
		ID3D11Device* device = GraphicsSystem::Instance()->GetGraphicsDevice();
		HRESULT createdPixelShader = device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, &m_pixelShader);
		SAFE_RELEASE(pixelShaderBlob);

		return SUCCEEDED(createdPixelShader);
	}
	else
	{
		return false;
	}
}
