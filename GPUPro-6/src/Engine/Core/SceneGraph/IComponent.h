#pragma once
#include "Engine/Core/RTTI/ITypedObject.h"

class IComponent : public ITypedObject
{
public:
	ToPtr entity;
	bool m_enabled = true;
};