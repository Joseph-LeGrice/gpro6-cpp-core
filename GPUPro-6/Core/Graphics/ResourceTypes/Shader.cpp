#include "stdafx.h"
#include "Core/Graphics/ResourceTypes/Shader.h"

#include "D3DX11.h"

#include "Core/Graphics/VertexData.h"
#include "Core/SystemManagement/SystemManager.h"
#include "Core/ResourceManagement/ResourceManager.h"

Shader::Shader(UINT resourceId) : IResource(resourceId)
{
}


void Shader::Release()
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
		ID3D11DeviceContext* deviceContext = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
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
    HRESULT vertexShaderCompileResult = D3DX11CompileFromFile(filename.c_str(), 0, 0, name.c_str(), "vs_5_0", 0, 0, 0, vertexShaderBlob, vertexShaderErrorBlob, 0);
	if (vertexShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)vertexShaderErrorBlob->GetBufferPointer());
	}

    bool result = false;
	if (SUCCEEDED(vertexShaderCompileResult))
	{
		ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();
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
    HRESULT hullShaderCompileResult = D3DX11CompileFromFile(filename.c_str(), 0, 0, name.c_str(), "hs_5_0", 0, 0, 0, hullShaderBlob, hullShaderErrorBlob, 0);
	if (hullShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)hullShaderErrorBlob->GetBufferPointer());
	}

	if (SUCCEEDED(hullShaderCompileResult))
	{
		ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();
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
    HRESULT domainShaderCompileResult = D3DX11CompileFromFile(filename.c_str(), 0, 0, name.c_str(), "ds_5_0", 0, 0, 0, domainShaderBlob, domainShaderErrorBlob, 0);
	if (domainShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)domainShaderErrorBlob->GetBufferPointer());
	}

	if (SUCCEEDED(domainShaderCompileResult))
	{
		ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();
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
    HRESULT geomShaderCompileResult = D3DX11CompileFromFile(filename.c_str(), 0, 0, name.c_str(), "gs_5_0", 0, 0, 0, geomShaderBlob, geomShaderErrorBlob, 0);
	if (geomShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)geomShaderErrorBlob->GetBufferPointer());
	}

	if (SUCCEEDED(geomShaderCompileResult))
	{
		ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();
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
    HRESULT pixelShaderCompileResult = D3DX11CompileFromFile(filename.c_str(), 0, 0, name.c_str(), "ps_5_0", 0, 0, 0, pixelShaderBlob, pixelShaderErrorBlob, 0);
	if (pixelShaderErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)pixelShaderErrorBlob->GetBufferPointer());
	}

	if (SUCCEEDED(pixelShaderCompileResult))
	{
		ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();
		HRESULT createdPixelShader = device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, m_pixelShader);

		return SUCCEEDED(createdPixelShader);
	}
	else
	{
		return false;
	}
}
