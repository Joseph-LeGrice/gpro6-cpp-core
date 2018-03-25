#pragma once

#include "Material.hpp"

class SimpleMaterial : public Material<void>
{
public:
	static ResourceTypeID GetResourceType()
	{
		return 11;
	}
};
