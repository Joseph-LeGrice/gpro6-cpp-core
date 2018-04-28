#pragma once

#include <string>
#include <vector>
#include "Engine/Core/RTTI/ITypedObject.h"

class GraphicsDevice;
struct ID3D11InputLayout;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11GeometryShader;
struct ID3D11HullShader;
struct ID3D11DomainShader;

class Shader : public ITypedObject
{
REGISTER_TYPE(Shader);
public:
	bool SetCurrentIfValid();

	bool InitVertexShader(std::wstring filename, std::string name);
	bool InitHullShader(std::wstring filename, std::string name);
	bool InitDomainShader(std::wstring filename, std::string name);
	bool InitGeometryShader(std::wstring filename, std::string name);
	bool InitPixelShader(std::wstring filename, std::string name);

	virtual void Finalize() override;

private:
    ManualRelease<ID3D11InputLayout> m_inputLayout;
    ManualRelease<ID3D11VertexShader> m_vertexShader;
    ManualRelease<ID3D11PixelShader> m_pixelShader;
    ManualRelease<ID3D11GeometryShader> m_geometryShader;
    ManualRelease<ID3D11HullShader> m_hullShader;
    ManualRelease<ID3D11DomainShader> m_domainShader;
};
