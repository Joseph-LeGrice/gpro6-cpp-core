#pragma once

#include "ConstantBuffer.h"
#include "GameSystem.h"

#include "Graphics/ConstantBuffers/PerObjectBuffer.h"

class ConstantBufferManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(ConstantBufferManagementSystem);
public:
	void ConstantBufferManagementSystem::SetBuffers()
	{
		ID3D11Buffer* const buf = m_perObjectBuffer.GetBuffer();

		ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
		deviceContext->VSSetConstantBuffers(0, 1, &buf);
		//deviceContext->HSSetConstantBuffers(0, 1, &buf);
		//deviceContext->DSSetConstantBuffers(0, 1, &buf);
		//deviceContext->GSSetConstantBuffers(0, 1, &buf);
		deviceContext->PSSetConstantBuffers(0, 1, &buf);
	}

	PerObjectBuffer& GetPerObjectBuffer()
	{
		return m_perObjectBuffer;
	}
private:
	PerObjectBuffer m_perObjectBuffer;
};
