#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
	m_shader = nullptr;
	m_mesh = nullptr;
	m_constBuffer = nullptr;
}

Renderer::~Renderer()
{
	SAFE_DELETE(m_shader);
	SAFE_DELETE(m_mesh);
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
			m_constBuffer = InitConstantBuffer(device);
			if (m_constBuffer != nullptr)
			{
				return true;
			}
		}
	}
	return false;
}

void Renderer::Render(ID3D11DeviceContext* deviceContext)
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
#
	ID3D11Buffer* constPSBuf = m_constBuffer->GetPSBuffer();
	if (constPSBuf != nullptr)
	{
		deviceContext->PSSetConstantBuffers(0, 1, &constPSBuf);
	}

	m_shader->SetCurrent(deviceContext);
	m_mesh->Render(deviceContext);
}

