#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
	m_mesh = nullptr;
	m_shader = nullptr;
	m_resources = nullptr;
	m_constBuffer = nullptr;
}

Renderer::~Renderer()
{
	SAFE_DELETE(m_mesh);
	SAFE_DELETE(m_shader);
	SAFE_DELETE(m_resources);
	SAFE_DELETE(m_constBuffer);
}

bool Renderer::Initialize(ID3D11Device* device)
{
	m_shader = InitShaders(device);
	if (m_shader != nullptr)
	{
		m_mesh = InitMesh(device);
		if (m_mesh != nullptr)
		{
			m_resources = InitResourceViews(device);
			m_constBuffer = InitConstantBuffer(device);
			return true;
		}
	}
	return false;
}

void Renderer::Render(ID3D11DeviceContext* deviceContext)
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

	if (m_resources != nullptr)
	{
		std::vector<ID3D11ShaderResourceView*>* vsResources = m_resources->GetVSResources();
		if (vsResources != nullptr && vsResources->size() > 0)
		{
			deviceContext->VSSetShaderResources(0, vsResources->size(), vsResources->data());
		}

		std::vector<ID3D11ShaderResourceView*>* hsResources = m_resources->GetHSResources();
		if (hsResources != nullptr && hsResources->size() > 0)
		{
			deviceContext->HSSetShaderResources(0, hsResources->size(), hsResources->data());
		}

		std::vector<ID3D11ShaderResourceView*>* dsResources = m_resources->GetDSResources();
		if (dsResources != nullptr && dsResources->size() > 0)
		{
			deviceContext->DSSetShaderResources(0, dsResources->size(), dsResources->data());
		}

		std::vector<ID3D11ShaderResourceView*>* gsResources = m_resources->GetGSResources();
		if (gsResources != nullptr && gsResources->size() > 0)
		{
			deviceContext->GSSetShaderResources(0, gsResources->size(), gsResources->data());
		}

		std::vector<ID3D11ShaderResourceView*>* psResources = m_resources->GetPSResources();
		if (psResources != nullptr && psResources->size() > 0)
		{
			deviceContext->PSSetShaderResources(0, psResources->size(), psResources->data());
		}
	}

	m_shader->SetCurrent(deviceContext);
	m_mesh->Render(deviceContext);
}

