#include "stdafx.h"
#include "Material.h"
#include "GameSystem.h"
#include "MaterialManagementSystem.h"

Material::Material()
{
	m_meshes = new std::vector<Mesh*>();
}


Material::~Material()
{
}

Material* Material::Create()
{
	Material* newMaterial = new Material();
	GameSystem::MaterialManager()->RegisterInstancedMaterial(newMaterial);
	return newMaterial;
}

bool Material::Initialize(ID3D11Device* device)
{
	m_constBuffer = new ConstantBuffer();
	bool compiledShader = CompileShader(device);
	bool initializedBuffers = InitializeBuffers(device);

	if (m_constBuffer->Initialize(device) && compiledShader && initializedBuffers)
	{
		return true;
	}
	else
	{
		SAFE_DELETE(m_constBuffer);
		SAFE_DELETE(m_shader);
		return false;
	}
}


void Material::RegisterMesh(Mesh* mesh)
{
	m_meshes->push_back(mesh);
}


bool Material::CompileShader(ID3D11Device* device)
{
	m_shader = new Shader();
	std::wstring filename = L"TriTessellation.shader";
	bool vertexShaderCompiled = m_shader->InitVertexShader(filename, "VShader", device);
	bool hullShaderCompiled = m_shader->InitHullShader(filename, "HShader", device);
	bool domainShaderCompiled = m_shader->InitDomainShader(filename, "DShader", device);
	bool geometryShaderCompiled = m_shader->InitGeometryShader(filename, "GShaderTessellation", device);
	bool pixelShaderCompiled = m_shader->InitPixelShader(filename, "SolidColorPShaderGeometry", device);

	if (vertexShaderCompiled && hullShaderCompiled && domainShaderCompiled && geometryShaderCompiled && pixelShaderCompiled)
	{
		return true;
	}
	else
	{
		SAFE_DELETE(m_shader);
		return false;
	}
}

bool Material::InitializeBuffers(ID3D11Device* device)
{
	std::vector<Vertex> allVerts;
	std::vector<UINT16> allIndices;
	for each (Mesh* m in *m_meshes)
	{
		const std::vector<Vertex>* verts = m->GetVertices();
		allVerts.insert(allVerts.end(), verts->begin(), verts->end());

		const std::vector<UINT16>* indices = m->GetIndices();
		allIndices.insert(allIndices.end(), indices->begin(), indices->end());
	}

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(UINT16) * allIndices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = allIndices.data();
	initialIndexData.SysMemPitch = 0;
	initialIndexData.SysMemSlicePitch = 0;

	HRESULT indexBufferCreationResult = device->CreateBuffer(&indexBufferDesc, &initialIndexData, &m_indexBuffer);
	bool indexBufferCreated = indexBufferCreationResult == S_OK;

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * allVerts.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	HRESULT vertexBufferCreation = device->CreateBuffer(&vertexBufferDesc, NULL, &m_vertexBuffer);
	bool vertexBufferCreated = vertexBufferCreation == S_OK;

	return indexBufferCreated && vertexBufferCreated;
}


void Material::Render(ID3D11DeviceContext* deviceContext)
{
	if (m_constBuffer != nullptr)
	{
		ID3D11Buffer* constVSBuf = m_constBuffer->GetVSBuffer();
		if (constVSBuf != nullptr)
		{
			deviceContext->VSSetConstantBuffers(0, 1, &constVSBuf);
		}

		ID3D11Buffer* constHSBuf = m_constBuffer->GetVSBuffer();
		if (constHSBuf != nullptr)
		{
			deviceContext->HSSetConstantBuffers(0, 1, &constHSBuf);
		}

		ID3D11Buffer* constDSBuf = m_constBuffer->GetVSBuffer();
		if (constDSBuf != nullptr)
		{
			deviceContext->DSSetConstantBuffers(0, 1, &constDSBuf);
		}

		ID3D11Buffer* constGSBuf = m_constBuffer->GetVSBuffer();
		if (constGSBuf != nullptr)
		{
			deviceContext->GSSetConstantBuffers(0, 1, &constGSBuf);
		}

		ID3D11Buffer* constPSBuf = m_constBuffer->GetPSBuffer();
		if (constPSBuf != nullptr)
		{
			deviceContext->PSSetConstantBuffers(0, 1, &constPSBuf);
		}
	}

	m_shader->SetCurrent(deviceContext);

	UINT offset = 0;
	UINT stride = sizeof(Vertex);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	int currentIndex = 0;
	for each (Mesh* m in *m_meshes)
	{
		int numberOfVerts = m->GetIndices()->size();
		deviceContext->IASetPrimitiveTopology(m->GetTopology());
		deviceContext->DrawIndexed(numberOfVerts, currentIndex, 0);
		currentIndex += numberOfVerts;
	}
}
