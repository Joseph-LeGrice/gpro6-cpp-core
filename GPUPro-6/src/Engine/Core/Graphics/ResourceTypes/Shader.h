#pragma once

#include "D3D11.h"
#include <string>
#include <vector>
#include "Engine/Core/ResourceManagement/IResource.h"

class Shader : public IResource
{
public:
	bool SetCurrentIfValid();

	bool InitVertexShader(std::wstring filename, std::string name);
	bool InitHullShader(std::wstring filename, std::string name);
	bool InitDomainShader(std::wstring filename, std::string name);
	bool InitGeometryShader(std::wstring filename, std::string name);
	bool InitPixelShader(std::wstring filename, std::string name);

	Shader(UINT resourceId);

    virtual void Release() override;

private:
    ManualRelease<ID3D11InputLayout> m_inputLayout;
    ManualRelease<ID3D11VertexShader> m_vertexShader;
    ManualRelease<ID3D11PixelShader> m_pixelShader;
    ManualRelease<ID3D11GeometryShader> m_geometryShader;
    ManualRelease<ID3D11HullShader> m_hullShader;
    ManualRelease<ID3D11DomainShader> m_domainShader;
};

