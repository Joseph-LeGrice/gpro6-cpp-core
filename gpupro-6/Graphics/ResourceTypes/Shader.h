#pragma once

#include "D3D11.h"
#include <string>
#include <vector>
#include "AssetManagement/IResource.h"

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
    ~Shader();

private:
	ID3D11InputLayout* m_inputLayout;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11GeometryShader* m_geometryShader;
	ID3D11HullShader* m_hullShader;
	ID3D11DomainShader* m_domainShader;
};

