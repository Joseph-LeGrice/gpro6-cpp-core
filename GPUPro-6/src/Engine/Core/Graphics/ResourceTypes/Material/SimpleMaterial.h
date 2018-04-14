#pragma once

#include "Material.hpp"
#include "Engine/Core/ResourceManagement/ResourceTypeMapping.h"

class SimpleMaterial : public Material<void>
{
public:
	static const RegisterResource<SimpleMaterial, 11> static_registration;
};
