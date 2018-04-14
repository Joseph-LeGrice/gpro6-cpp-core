#pragma once

#include "Material.hpp"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/StandardMaterialBuffer.h"
#include "Engine/Core/ResourceManagement/ResourceTypeMapping.h"

class StandardMaterial : public Material<MATERIAL_BUFFER_CONTAINER>
{
public:
	static const RegisterResource<StandardMaterial, 10> static_registration;
};