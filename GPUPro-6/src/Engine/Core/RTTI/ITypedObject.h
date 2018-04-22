#pragma once

#include "TypeMapping.h"
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
	TypeID m_typeId;
	InstanceID m_instanceId;
};
