#pragma once

#include "Material.hpp"
#include "Engine/Core/ResourceManagement/ResourceTypeMapping.h"

class SimpleMaterial : public Material<void>
{
public:
	REGISTER_RESOURCE(SimpleMaterial, 11)
};
