#include "stdafx.h"
#include "Shader.h"

#include "D3D11.h"
#include <d3dcompiler.h>

#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/Graphics/VertexData.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/GlobalStaticReferences.h"

static const D3D11_INPUT_ELEMENT_DESC g_inputLayoutScheme[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

void Shader::Finalize()
{
    m_inputLayout.ReleasePointer();
    m_vertexShader.ReleasePointer();
    m_pixelShader.ReleasePointer();
    m_geometryShader.ReleasePointer();
    m_hullShader.ReleasePointer();
    m_domainShader.ReleasePointer();
}

bool Shader::SetCurrentIfValid()
{
	if (m_vertexShader == nullptr || m_inputLayout == nullptr || m_pixelShader == nullptr)
	{
		return false;
	}
	else
	{
		ID3D11DeviceContext* deviceContext = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDeviceContext();
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
    AutoRelease<ID3D10Blob> vertexShaderErrorBlob;
    AutoRelease<ID3D10Blob> vertexShaderBlob;
    HRESULT vertexShaderCompileResult = D3DCompileFromFile(filename.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, name.c_str(), "vs_5_0", 0, 0, vertexShaderBlob, vertexShaderErrorBlob);
	if (vertexShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)vertexShaderErrorBlob->GetBufferPointer());
	}

    bool result = false;
	if (SUCCEEDED(vertexShaderCompileResult))
	{
		ID3D11Device* device = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDevice();
		HRESULT createdVertexShader  = device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, m_vertexShader);
		if (SUCCEEDED(createdVertexShader))
		{
			HRESULT attachedInputLayout = device->CreateInputLayout(g_inputLayoutScheme, 5, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), m_inputLayout);
			result = SUCCEEDED(attachedInputLayout);
		}
	}

	return result;
}


bool Shader::InitHullShader(std::wstring filename, std::string name)
{
    AutoRelease<ID3D10Blob> hullShaderErrorBlob;
    AutoRelease<ID3D10Blob> hullShaderBlob;
    HRESULT hullShaderCompileResult = D3DCompileFromFile(filename.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, name.c_str(), "hs_5_0", 0, 0, hullShaderBlob, hullShaderErrorBlob);
	if (hullShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)hullShaderErrorBlob->GetBufferPointer());
	}

	if (SUCCEEDED(hullShaderCompileResult))
	{
		ID3D11Device* device = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDevice();
		HRESULT createdHullShader = device->CreateHullShader(hullShaderBlob->GetBufferPointer(), hullShaderBlob->GetBufferSize(), NULL, m_hullShader);
		
		return SUCCEEDED(createdHullShader);
	}
	else
	{
		return false;
	}
}


bool Shader::InitDomainShader(std::wstring filename, std::string name)
{
    AutoRelease<ID3D10Blob> domainShaderErrorBlob;
    AutoRelease<ID3D10Blob> domainShaderBlob;
    HRESULT domainShaderCompileResult = D3DCompileFromFile(filename.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, name.c_str(), "ds_5_0", 0, 0, domainShaderBlob, domainShaderErrorBlob);
	if (domainShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)domainShaderErrorBlob->GetBufferPointer());
	}

	if (SUCCEEDED(domainShaderCompileResult))
	{
		ID3D11Device* device = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDevice();
		HRESULT createdDomainShader = device->CreateDomainShader(domainShaderBlob->GetBufferPointer(), domainShaderBlob->GetBufferSize(), 0, m_domainShader);

		return SUCCEEDED(createdDomainShader);
	}
	else
	{
		return false;
	}
}


bool Shader::InitGeometryShader(std::wstring filename, std::string name)
{
    AutoRelease<ID3D10Blob> geomShaderErrorBlob;
    AutoRelease<ID3D10Blob> geomShaderBlob;
    HRESULT geomShaderCompileResult = D3DCompileFromFile(filename.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, name.c_str(), "gs_5_0", 0, 0, geomShaderBlob, geomShaderErrorBlob);
	if (geomShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)geomShaderErrorBlob->GetBufferPointer());
	}

	if (SUCCEEDED(geomShaderCompileResult))
	{
		ID3D11Device* device = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDevice();
		HRESULT createdGeometryShader = device->CreateGeometryShader(geomShaderBlob->GetBufferPointer(), geomShaderBlob->GetBufferSize(), NULL, m_geometryShader);

		return SUCCEEDED(createdGeometryShader);
	}
	else
	{
		return false;
	}
}

	
bool Shader::InitPixelShader(std::wstring filename, std::string name)
{
    AutoRelease<ID3D10Blob> pixelShaderErrorBlob;
    AutoRelease<ID3D10Blob> pixelShaderBlob;
    HRESULT pixelShaderCompileResult = D3DCompileFromFile(filename.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, name.c_str(), "ps_5_0", 0, 0, pixelShaderBlob, pixelShaderErrorBlob);
	if (pixelShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)pixelShaderErrorBlob->GetBufferPointer());
	}

	if (SUCCEEDED(pixelShaderCompileResult))
	{
		ID3D11Device* device = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDevice();
		HRESULT createdPixelShader = device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, m_pixelShader);

		return SUCCEEDED(createdPixelShader);
	}
	else
	{
		return false;
	}
}
