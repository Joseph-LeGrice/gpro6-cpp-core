#pragma once

#include "TypeNameMapping.h"
#include "RTTI.h"

class ITypedObject
{
friend class TypedObjectManager;
public:
	virtual const char* GetTypeName() = 0;
	
	InstanceID GetInstanceID()
	{
		return m_instanceId;
	}

private:
	InstanceID m_instanceId;
};
