#pragma once

#include "ConstantBuffer.h"
#include "GameSystem.h"

#include "Graphics/ConstantBuffers/ConstantBufferDefines.h"

#define REGISTER_BUFFER(bufferType) \
public: \
	bufferType& Get##bufferType##() \
	{ \
		return m_##bufferType##Buffer; \
	} \
private: \
	bufferType m_##bufferType##Buffer; \

class ConstantBufferManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(ConstantBufferManagementSystem);

	REGISTER_BUFFER(PerObjectBuffer);
	REGISTER_BUFFER(MaterialBuffer);
};


