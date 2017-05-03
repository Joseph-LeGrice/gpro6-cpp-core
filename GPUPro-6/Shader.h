#pragma once

#include "D3D11.h"
#include "InputLayout.h"
#include <string>

class Shader
{
public:
	Shader();
	~Shader();

	bool InitVertexShader(std::wstring filename, std::string name, ID3D11Device* device, InputLayout* iLayout);
	bool InitHullShader(std::wstring filename, std::string name, ID3D11Device* device);
	bool InitDomainShader(std::wstring filename, std::string name, ID3D11Device* device);
	bool InitGeometryShader(std::wstring filename, std::string name, ID3D11Device* device);
	bool InitPixelShader(std::wstring filename, std::string name, ID3D11Device* device);
	
	void SetCurrent(ID3D11DeviceContext* deviceContext);

private:
	ID3D11InputLayout* m_inputLayout;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11GeometryShader* m_geometryShader;
	ID3D11HullShader* m_hullShader;
	ID3D11DomainShader* m_domainShader;
};

