#pragma once

#include "D3D11.h"
#include <string>
#include <vector>

class Shader
{
	friend class ShaderManagementSystem;

public:
	static Shader* CreateFromFile(std::wstring filename);
	bool SetCurrentIfValid();

private:
	bool InitVertexShader(std::wstring filename, std::string name, ID3D11Device* device);
	bool InitHullShader(std::wstring filename, std::string name, ID3D11Device* device);
	bool InitDomainShader(std::wstring filename, std::string name, ID3D11Device* device);
	bool InitGeometryShader(std::wstring filename, std::string name, ID3D11Device* device);
	bool InitPixelShader(std::wstring filename, std::string name, ID3D11Device* device);

	ID3D11InputLayout* m_inputLayout;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11GeometryShader* m_geometryShader;
	ID3D11HullShader* m_hullShader;
	ID3D11DomainShader* m_domainShader;

	Shader();
	~Shader();
};

