#include "stdafx.h"
#include "Shader.h"

#include "D3DX11.h"

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

	if (vertexShaderCompileResult == S_OK)
	{
		bool createdVertexShader = device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &m_vertexShader) == S_OK;

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		bool createdInputLayer = device->CreateInputLayout(ied, 2, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &m_inputLayout) == S_OK;

		SAFE_RELEASE(vertexShaderBlob);

		return createdVertexShader && createdInputLayer;
	}
	else
	{
		return false;
	}
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

	if (hullShaderCompileResult == S_OK)
	{
		bool createdHullShader = device->CreateHullShader(hullShaderBlob->GetBufferPointer(), hullShaderBlob->GetBufferSize(), NULL, &m_hullShader) == S_OK;
		SAFE_RELEASE(hullShaderBlob);

		return createdHullShader;
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

	if (domainShaderCompileResult == S_OK)
	{
		bool createdDomainShader = device->CreateDomainShader(domainShaderBlob->GetBufferPointer(), domainShaderBlob->GetBufferSize(), 0, &m_domainShader) == S_OK;
		SAFE_RELEASE(domainShaderBlob);

		return createdDomainShader;
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

	if (geomShaderCompileResult == S_OK)
	{
		bool createdGeometryShader = device->CreateGeometryShader(geomShaderBlob->GetBufferPointer(), geomShaderBlob->GetBufferSize(), NULL, &m_geometryShader) == S_OK;
		SAFE_RELEASE(geomShaderBlob);

		return createdGeometryShader;
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

	if (pixelShaderCompileResult == S_OK)
	{
		bool createdPixelShader = device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, &m_pixelShader) == S_OK;
		SAFE_RELEASE(pixelShaderBlob);

		return createdPixelShader;
	}
	else
	{
		return false;
	}
}

void Shader::SetCurrent(ID3D11DeviceContext* deviceContext)
{
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
}
