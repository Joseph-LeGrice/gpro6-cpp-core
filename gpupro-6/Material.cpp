#include "stdafx.h"
#include "Material.h"
#include "GameSystem.h"
#include "MaterialManagementSystem.h"
#include "GraphicsSystem.h"

Material::Material()
{
	m_shader = nullptr;
	m_constBuffer = nullptr;
	m_meshes = new std::vector<Mesh*>();
}


Material::~Material()
{
	SAFE_DELETE(m_shader);
	SAFE_DELETE(m_constBuffer);
}

Material* Material::Create()
{
	Material* newMaterial = new Material();
	if (newMaterial->Initialize())
	{
		GameSystem::MaterialManager()->RegisterInstancedMaterial(newMaterial);
		return newMaterial;
	}
	else
	{
		SAFE_DELETE(newMaterial);
		return nullptr;
	}
}

bool Material::Initialize()
{
	ID3D11Device* device = GameSystem::Graphics()->GetGraphicsDevice();
	m_constBuffer = new ConstantBuffer(); //todo: Move constant buffer out of material
	bool initializeConstantBuffer = m_constBuffer->Initialize();
	bool initializedBuffers = InitializeBuffers();

	if (initializeConstantBuffer && initializedBuffers)
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


void Material::CompileShader(std::wstring filename)
{
	if (m_shader != nullptr)
	{
		SAFE_DELETE(m_shader);
	}

	m_shader = new Shader();
	ID3D11Device* device = GameSystem::Graphics()->GetGraphicsDevice(); 
	bool vertexShaderCompiled = m_shader->InitVertexShader(filename, "VShader", device);
	bool hullShaderCompiled = true; // = m_shader->InitHullShader(filename, "HShader", device);
	bool domainShaderCompiled = true; //= m_shader->InitDomainShader(filename, "DShader", device);
	bool geometryShaderCompiled = true; // = m_shader->InitGeometryShader(filename, "GShaderTessellation", device);
	bool pixelShaderCompiled = m_shader->InitPixelShader(filename, "PShader", device);

	if (vertexShaderCompiled && hullShaderCompiled && domainShaderCompiled && geometryShaderCompiled && pixelShaderCompiled)
	{
	}
	else
	{
		SAFE_DELETE(m_shader);
	}
}

bool Material::InitializeBuffers()
{
	ID3D11Device* device = GameSystem::Graphics()->GetGraphicsDevice();
	
	int INDEX_BUFFER_SIZE = 1024;
	int VERTEX_BUFER_SIZE = 1024;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	indexBufferDesc.ByteWidth = sizeof(UINT16) * INDEX_BUFFER_SIZE;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufferDesc.MiscFlags = 0;

	HRESULT indexBufferCreationResult = device->CreateBuffer(&indexBufferDesc, NULL, &m_indexBuffer);
	bool indexBufferCreated = indexBufferCreationResult == S_OK;

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * VERTEX_BUFER_SIZE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	HRESULT vertexBufferCreation = device->CreateBuffer(&vertexBufferDesc, NULL, &m_vertexBuffer);
	bool vertexBufferCreated = vertexBufferCreation == S_OK;

	return indexBufferCreated && vertexBufferCreated;
}


void Material::Render()
{
	ID3D11DeviceContext* deviceContext = GameSystem::Graphics()->GetGraphicsDeviceContext();
	if (m_constBuffer != nullptr)
	{
		ID3D11Buffer* constVSBuf = m_constBuffer->GetVSBuffer();
		if (constVSBuf != nullptr)
		{
			deviceContext->VSSetConstantBuffers(0, 1, &constVSBuf);
		}

		ID3D11Buffer* constHSBuf = m_constBuffer->GetHSBuffer();
		if (constHSBuf != nullptr)
		{
			deviceContext->HSSetConstantBuffers(0, 1, &constHSBuf);
		}

		ID3D11Buffer* constDSBuf = m_constBuffer->GetDSBuffer();
		if (constDSBuf != nullptr)
		{
			deviceContext->DSSetConstantBuffers(0, 1, &constDSBuf);
		}

		ID3D11Buffer* constGSBuf = m_constBuffer->GetGSBuffer();
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

	std::vector<Vertex> allVerts;
	std::vector<UINT16> allIndices;
	for each (Mesh* m in *m_meshes)
	{
		const std::vector<Vertex>* verts = m->GetVertices();
		allVerts.insert(allVerts.end(), verts->begin(), verts->end());

		const std::vector<UINT16>* indices = m->GetIndices();
		allIndices.insert(allIndices.end(), indices->begin(), indices->end());
	}

	D3D11_MAPPED_SUBRESOURCE vertexData;
	HRESULT vertexBufferAcquireResult = deviceContext->Map(m_vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &vertexData);
	if (vertexBufferAcquireResult == S_OK)
	{
		memcpy(vertexData.pData, &allVerts[0], sizeof(Vertex) * allVerts.size());
		deviceContext->Unmap(m_vertexBuffer, 0);
	}

	D3D11_MAPPED_SUBRESOURCE indexBufferData;
	HRESULT indexBufferAcquireResult = deviceContext->Map(m_indexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &indexBufferData);
	if (indexBufferAcquireResult == S_OK)
	{
		memcpy(indexBufferData.pData, &allIndices[0], sizeof(UINT16) * allIndices.size());
		deviceContext->Unmap(m_indexBuffer, 0);
	}

	int currentIndex = 0;
	for each (Mesh* m in *m_meshes)
	{
		int numberOfVerts = m->GetIndices()->size();
		deviceContext->IASetPrimitiveTopology(m->GetTopology());
		deviceContext->DrawIndexed(numberOfVerts, currentIndex, 0);
		currentIndex += numberOfVerts;
	}
}
