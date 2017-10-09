#pragma once

#include "ConstantBuffer.h"
#include "GameSystem.h"

#include "Graphics/ConstantBuffers/ConstantBufferDefines.h"


class ConstantBufferManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(ConstantBufferManagementSystem);

public:
	PerObjectBuffer& GetPerObjectBuffer()
	{
		return m_perObjectBuffer;
	}
private:
	PerObjectBuffer m_perObjectBuffer;


public:
	MaterialBuffer& GetMaterialBuffer()
	{
		return m_materialBuffer;
	}
private:
	MaterialBuffer m_materialBuffer;
};


