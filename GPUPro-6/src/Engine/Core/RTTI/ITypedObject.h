#pragma once

#include "TypeNameMapping.h"
#include "RTTI.h"

class ITypedObject
{
friend class TypedObjectManager;
public:
	virtual void Establish() { }
	virtual void Finalize() { }

	InstanceID GetInstanceID()
	{
		return m_instanceId;
	}

private:
	InstanceID m_instanceId;
};