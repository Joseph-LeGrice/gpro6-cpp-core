#pragma once

#include "Material.hpp"


class SimpleMaterial : public Material<void>
{
public:
	virtual const char* GetTypeName() override
	{
		return TO_STRING(SimpleMaterial);
	}
};
REGISTER_TYPE(SimpleMaterial, 11)
