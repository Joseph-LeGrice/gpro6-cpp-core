#pragma once

#include "Material.hpp"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/StandardMaterialBuffer.h"


class StandardMaterial : public Material<MATERIAL_BUFFER_CONTAINER>
{
public:
	virtual const char* GetTypeName() override
	{
		return TO_STRING(StandardMaterial);
	}
};
REGISTER_TYPE(StandardMaterial, 10)
