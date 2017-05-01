#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
	m_shader = nullptr;
	m_mesh = nullptr;
}

Renderer::~Renderer()
{
	SAFE_DELETE(m_shader);
	SAFE_DELETE(m_mesh);
}

bool Renderer::Initialize(ID3D11Device* device)
{
	m_shader = InitShaders(device);
	if (m_shader != nullptr)
	{
		m_mesh = InitMesh(device);
		if (m_mesh != nullptr)
		{
			return true;
		}
	}
	return false;
}

void Renderer::Render(ID3D11DeviceContext* deviceContext)
{
	m_shader->SetCurrent(deviceContext);
	m_mesh->Render(deviceContext);
}

